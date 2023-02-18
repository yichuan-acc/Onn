[org 0x1000]

dw 0x55aa; 魔数，用于判断错误

xchg bx,bx;

mov si,loading
call print

; jmp error

xchg bx,bx

detect_memory:
    ;ebx置为0
    xor ebx,ebx

    ;es:di结构体的缓存位置
    mov ax,0
    mov es,ax
    mov edi,ards_buffer

    mov edx,0x534d4150;固定签名

.next:
    ; 子功能号
    mov eax, 0xe820
    ; ards 结构的大小 (字节)
    mov ecx, 20
    ; 调用 0x15 系统调用
    int 0x15

    ; 如果 CF 置位，表示出错
    jc error

    ; 将缓存指针指向下一个结构体
    add di, cx

    ; 将结构体数量加一
    inc word [ards_count]

    cmp ebx, 0
    jnz .next

    mov si, detecting
    call print

    xchg bx, bx

    mov cx,[ards_count]
    mov si,0

;0到9f00可以被使用
.show:
    mov eax,[ards_buffer+si]
    mov ebx,[ards_buffer+si+8]
    mov edx,[ards_buffer+si+16]
    add si,20
    xchg bx,bx
    loop .show

jmp $

print:
    mov ah, 0x0e
.next:
    mov al, [si]
    cmp al, 0
    jz .done
    int 0x10
    inc si
    jmp .next
.done:
    ret

loading:
    db "loading Onix...",10,13,0; \n\r

detecting:
    db "Detecting Memory Success...",10,13,0;\n\r

error:
    mov si, .msg
    call print
    hlt; 让 CPU 停止
    jmp $
    .msg db "Booting Error!!!", 10, 13, 0

ards_count:
    dd 0
ards_buffer:

