#include <onix/stdarg.h>
#include <onix/console.h>
#include <onix/stdio.h>

// 存储输出字符串
static char buf[1024];

int printk(const char *fmt, ...)
{
    va_list args;
    int i;

    va_start(args, fmt);

    // 格式化输出到buf里面
    i = vsprintf(buf, fmt, args);

    va_end(args);

    console_write(buf, i);

    return i;
}
