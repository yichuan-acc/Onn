[org 0x1000]

dw 0x55aa; 魔数，用于判断错误

mov si,loading
call print

; jmp error

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

error:
    mov si, .msg
    call print
    hlt; 让 CPU 停止
    jmp $
    .msg db "Booting Error!!!", 10, 13, 0





#
ards_count:
    dd 0
ards_buffer:

