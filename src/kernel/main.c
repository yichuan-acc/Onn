#include <onix/onix.h>
#include <onix/types.h>
#include <onix/io.h>

#define CRT_ADDR_REG 0X3d4
#define CRT_DATA_REG 0X3d5

#define CRT_CURSOR_H 0Xe
#define CRT_CURSOR_L 0Xf

void kernel_init()
{

    outb(CRT_ADDR_REG, CRT_CURSOR_H);
    u16 pos = inb(CRT_DATA_REG) << 8;

    outb(CRT_ADDR_REG, CRT_CURSOR_L);

    pos |= inb(CRT_DATA_REG);
    // u8 data = inb(CRT_DATA_REG);

    outb(CRT_ADDR_REG, CRT_CURSOR_H);
    outb(CRT_DATA_REG, 0);
    outb(CRT_ADDR_REG, CRT_CURSOR_L);
    outb(CRT_DATA_REG, 123);

    return;
}