#include <onix/interrupt.h>
#include <onix/assert.h>
#include <onix/debug.h>

#define LOGK(fmt, args...) DEBUGK(fmt, ##args)

// 系统调用函数表
#define SYSCALL_SIZE 64

handler_t syscall_table[SYSCALL_SIZE];

void syscall_check(u32 nr)
{
    if (nr >= SYSCALL_SIZE)
    {
        panic("syscall nr error!!!");
    }
}

//
static void sys_default()
{
    // 系统调用没有实现
    panic("syscall not implemented!!!");
}

static u32 sys_test()
{
    LOGK("syscall test...\n");
    return 255;
}

//
void syscall_init()
{
    for (size_t i = 0; i < SYSCALL_SIZE; i++)
    {
        // 首先把系统调用表设置为默认的
        syscall_table[i] = sys_default;
    }

    // 0 号测试的系统调用
    syscall_table[0] = sys_test; // ^
}
