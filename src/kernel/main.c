#include <onix/onix.h>
#include <onix/types.h>
#include <onix/io.h>
#include <onix/string.h>

// CRT地址寄存器 0x3D4
// CRT数据寄存器 0x3D5
// CRT光标位置 高位 0xE
// CRT光标位置 低位 0xF

#define CRT_ADDR_REG 0X3d4
#define CRT_DATA_REG 0X3d5

#define CRT_CURSOR_H 0Xe
#define CRT_CURSOR_L 0Xf

char message[] = "hello onix!!!";
char buf[1024];

void kernel_init()
{

    // outb(CRT_ADDR_REG, CRT_CURSOR_H);
    // u16 pos = inb(CRT_DATA_REG) << 8;

    // outb(CRT_ADDR_REG, CRT_CURSOR_L);

    // pos |= inb(CRT_DATA_REG);
    // // u8 data = inb(CRT_DATA_REG);

    // outb(CRT_ADDR_REG, CRT_CURSOR_H);
    // outb(CRT_DATA_REG, 0);
    // outb(CRT_ADDR_REG, CRT_CURSOR_L);
    // outb(CRT_DATA_REG, 123);

    int res;

    res = strcmp(buf, message);
    strcpy(buf, message);
    res = strcmp(buf, message);

    strcat(buf, message); // buf 为 两个 message

    res = strcmp(buf, message);

    res = strlen(message);

    res = sizeof(message);

    char *ptr = strchr(message, "!");
    ptr = strchr(message, '!');

    memset(buf, 0, sizeof(buf));

    res = memcmp(buf, message, sizeof(message));

    memcpy(buf, message, sizeof(message));

    ptr = memchr(buf, '!', sizeof(message));

        return;
}