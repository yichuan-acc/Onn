#ifndef ONIX_TASK_H
#define ONIX_TASK_H

#include <onix/types.h>

// 入口地址
typedef u32 target_t();

// 进程栈底在 esp 放高位置
typedef struct task_t
{
    u32 *stack; // 内核栈
} task_t;

// 寄存器，进程切换要保存，结束要恢复
typedef struct task_frame_t
{
    u32 edi;
    u32 esi;
    u32 ebx;
    u32 ebp;
    void (*eip)(void);
} task_frame_t;

// 初始化任务函数
void task_init();

#endif