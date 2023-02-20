[bits 32]

extern kernel_init
extern memory_init
extern console_init

global _start
_start:
    push ebx;ards_count
    push eax;magic

    call console_init; 控制台初始化
    call memory_init;内存初始化

    ; call kernel_init
    ; xchg bx,bx
    ; int 0x80;调用 0x80 中断函数

    ; mov bx,0
    ; div bx

    jmp $; 阻塞
