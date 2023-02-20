#include <onix/onix.h>
#include <onix/types.h>
#include <onix/io.h>
#include <onix/string.h>
#include <onix/console.h>
#include <onix/stdarg.h>
#include <onix/printk.h>
#include <onix/assert.h>
#include <onix/debug.h>
#include <onix/global.h>
#include <onix/task.h>
#include <onix/interrupt.h>
#include <onix/stdlib.h>

// 参数传递，从右向左压入栈中
// 所以先读取左边参数
void test_arg(int cnt, ...)
{
    va_list args;

    // args获取了参数的列表
    va_start(args, cnt);

    int arg;
    while (cnt--)
    {
        arg = va_arg(args, int);
    }
    va_end(args);
}

void test_printk()
{
    int cnt = 30;
    while (cnt--)
    {
        /* code */
        printk("hello world sss  %#010x\n", cnt);
    }
}

void test_assert()
{
    assert(3 < 5);
    assert(3 > 5);
}

void test_panic()
{
    panic("..Out Of Memory");
}

void test_debug()
{
    BMB;
    DEBUGK("debug onix!!!\n");
}

void kernel_init()
{
    console_init();
    gdt_init();
    interrupt_init();
    // task_init();

    asm volatile(
        "sti\n"
        "movl %eax,%eax\n");

    u32 counter = 0;
    while (true)
    {
        /* code */
        DEBUGK("looping in kernel init %d...\n", counter++);
        delay(100000000);
    }

    return;
}