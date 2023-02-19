#ifndef ONIX_ASSERT_H
#define ONIX_ASSERT_H

// 断言失败函数
void assertion_failure(char *exp, char *file, char *base, int line);

#define assert(exp) \
    if (exp)        \
        ;           \
    else            \
        assertion_failure(#exp, __FILE__, __BASE_FILE__, __LINE__)
// 这个通过宏 __FILE__ 表示当前文件,__BASE_FILE__,__LINE__
// #exp就是传入的表达式的字符串例如 3>5 ,出错所在文件和出错行数

// 出错
void panic(const char *fmt, ...);

#endif
