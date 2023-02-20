#include <onix/stdlib.h>

// 延迟
void delay(u32 count)
{
    while (count--)
        ;
}

// 阻塞函数
void hang()
{
    while (true)
        ;
}
