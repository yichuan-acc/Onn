[bits 32]

extern kernel_init
extern gdt_init
extern memory_init
extern console_init

global _start
_start:
    push ebx;ards_count
    push eax;magic

    call console_init; 控制台初始化
    call gdt_init;全局描述符初始化
    call memory_init;内存初始化 ,需要两个参数
    call kernel_init;内核初始化

    ; xchg bx,bx

    ; mov eax,0; 0 号系统调用
    ; int 0x80;
    ; call kernel_init
    ; xchg bx,bx
    ; int 0x80;调用 0x80 中断函数

    ; mov bx,0
    ; div bx


    jmp $; 阻塞
