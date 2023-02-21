#include <onix/task.h>
#include <onix/printk.h>
#include <onix/debug.h>
#include <onix/memory.h>
#include <onix/assert.h>
#include <onix/interrupt.h>
#include <onix/string.h>
#include <onix/bitmap.h>

extern bitmap_t kernel_map;
extern void task_switch(task_t *next);

#define NR_TASKS 64

// 所有任务的数组 task_table
static task_t *task_table[NR_TASKS];

// 从 task_table 里获得一个空闲的任务
static task_t *get_free_task()
{
    for (size_t i = 0; i < NR_TASKS; i++)
    {
        if (task_table[i] == NULL)
        {
            task_table[i] = (task_t *)alloc_kpage(1); // todo free_kpage
            return task_table[i];                     // 返回一个任务
        }
    }
    panic("No more tasks");
}

// 从任务数组中查找  某种状态  的任务，自己除外
static task_t *task_search(task_state_t state)
{
    // 在不可中断状态下，原子操作
    assert(!get_interrupt_state());
    task_t *task = NULL;
    task_t *current = running_task();

    for (size_t i = 0; i < NR_TASKS; i++)
    {
        task_t *ptr = task_table[i];
        if (ptr == NULL)
            continue;

        if (ptr->state != state)
            continue;
        if (current == ptr)
            continue;

        // task 为空 || task时间片小于ptr的(优先级更高) || 选择最晚执行的那个
        if (task == NULL || task->ticks < ptr->ticks || ptr->jiffies < task->jiffies)
            task = ptr;
    }

    return task;
}

// #define PAGE_SIZE 0X1000

// task_t *a = (task_t *)0x1000;
// task_t *b = (task_t *)0x2000;

// extern void task_switch(task_t *next);

// 把PCB放到内核栈的开头
task_t *running_task()
{
    // 获取当前任务
    asm volatile(
        "movl %esp, %eax\n"
        "andl $0xfffff000, %eax\n");
}

void schedule()
{
    task_t *current = running_task();

    // 数组中找到一个就绪状态的任务
    task_t *next = task_search(TASK_READY);

    assert(next != NULL);
    assert(next->magic == ONIX_MAGIC);

    // 当前状态为执行，就变成就绪
    if (current->state == TASK_RUNNING)
    {
        current->state = TASK_READY;
    }

    //
    if (!current->ticks)
    {
        current->ticks = current->priority;
    }

    // 下一个进程开始执行
    next->state = TASK_RUNNING;

    // 相等就不需要切换
    if (next == current)
        return;

    // 任务切换
    task_switch(next);
}

static task_t *task_create(target_t target, const char *name, u32 priority, u32 uid)
{
    // 得到一页内存
    task_t *task = get_free_task();
    memset(task, 0, PAGE_SIZE);

    u32 stack = (u32)task + PAGE_SIZE;

    stack -= sizeof(task_frame_t);
    task_frame_t *frame = (task_frame_t *)stack;
    frame->ebx = 0x11111111;
    frame->esi = 0x22222222;
    frame->edi = 0x33333333;
    frame->ebp = 0x44444444;
    frame->eip = (void *)target;

    strcpy((char *)task->name, name);

    task->stack = (u32 *)stack;
    task->priority = priority;
    task->ticks = task->priority;
    task->jiffies = 0;
    task->state = TASK_READY;
    task->uid = uid;
    task->vmap = &kernel_map;
    task->pde = KERNEL_PAGE_DIR; // page directory entry
    task->magic = ONIX_MAGIC;

    BMB;
    return task;
}

//
static void task_setup()
{
    task_t *task = running_task();
    task->magic = ONIX_MAGIC;
    task->ticks = 1; // 处理处 task->ticks-- 刚好调度

    memset(task_table, 0, sizeof(task_table));
}

// u32 _ofp thread_a()

u32 thread_a()
{
    // BMB;
    // 中断返回后，中断关闭
    // asm volatile("sti\n");
    set_interrupt_state(true);

    while (true)
    {
        printk("A");
        // schedule();
    }
}

u32 thread_b()
{
    // asm volatile("sti\n");
    set_interrupt_state(true);
    while (true)
    {
        printk("B");
        // schedule();
    } // 使用while 方法，函数退出有其他的方法。
}
u32 thread_c()
{
    // asm volatile("sti\n");
    set_interrupt_state(true);
    while (true)
    {
        printk("C");
        // schedule();
    }
}

void task_init()
{
    task_setup();

    // 内核用户的3个线程
    task_create(thread_a, "a", 5, KERNEL_USER);
    task_create(thread_b, "b", 5, KERNEL_USER);
    task_create(thread_c, "c", 5, KERNEL_USER);
}
