#ifndef ONIX_STDARG_H
#define ONIX_STDARG_H

// 指针保存可变参数
typedef char *va_list;

// 启用可变参数5 ... , args,cnt
// 传递进来的参数 5,1,0xaa,44 这一些是相邻空间的内存
// 所以这里需要获取地址后 + sizeof(char*) 这样才是第一个参数
#define va_start(ap, v) (ap = (va_list)&v + sizeof(char *))

// 获取下一个参数，ap自增了，但是返回的是计算后的结果(当前)
#define va_arg(ap, t) (*(t *)((ap += sizeof(char *)) - sizeof(char *)))

// 结束可变参数
#define va_end(ap) (ap = (va_list)0)

#endif
