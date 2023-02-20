#ifndef ONIX_STDLIB_H
#define ONIX_STDLIB_H

#include <onix/types.h>

#define MAX(a, b) (a < b ? b : a)
#define MIN(a, b) (a < b ? a : b)

void hang();
void delay(u32 count);

// BCD码 转换为二进制
u8 bcd_to_bin(u8 value);

// 二进制转换为 BCD 码
u8 bin_to_bcd(u8 value);

u32 div_round_up(u32 num, u32 size);

#endif