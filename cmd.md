# README

# 先让程序跑起来，剩下的以后再说
line for cmd in shell

> for command in selection

' ' for command in file


---------BEGIN-----------------
nasm -f bin boot.asm -o boot.bin



bximage -q -hd=16 -func=create -sectsize=512 -imgmode=flat master.img


dd if=boot.bin of=master.img bs=512 count=1 conv=notrunc

bochs
> 4
> bochsrc
> 7

'bochsrc'>13:
change 'ata0-master':type=disk, path="master.img", mode=flat

'bochsrc'>8:
change 'floppy' to 'disk'

'bochsrc'>4:
add 'options="gui_debug"'

bochs -q


在第二个扇区开始的4个扇区写入了内核加载器,
实模式的内存布局

#通过0x15来获取结构体来临时看一下内存的布局

启动的时候是8086模式 1M内存 病毒可以完全能控制计算机
要进入保护模式 80286 实模式 16位





# 13 编译和连接
创建了include/onix/onix.h

```shell
预编译并且写到 test.c
gcc -m32 -E main.c -I../include > test.c

编译成汇编文件
gcc -m32 -S test.c > test.s

汇编成可执行文件
as -32 test.s -o test.o

链接
ld -m elf_i386 -static test.o -o test.out -e kernel_init

```
> gcc 将上面所有的编译过程集成一起
    gcc -m32 main.c -I../include -o main.out -e kernel_init -nostartfiles

查看gcc编译细节
gcc --verbose -m32 main.c -I../include -o main.out -e kernel_init -nostartfiles

```console
Using built-in specs.
COLLECT_GCC=gcc
COLLECT_LTO_WRAPPER=/usr/lib/gcc/x86_64-pc-linux-gnu/12.2.1/lto-wrapper
Target: x86_64-pc-linux-gnu
Configured with: /build/gcc/src/gcc/configure --enable-languages=c,c++,ada,fortran,go,lto,objc,obj-c++,d --enable-bootstrap --prefix=/usr --libdir=/usr/lib --libexecdir=/usr/lib --mandir=/usr/share/man --infodir=/usr/share/info --with-bugurl=https://bugs.archlinux.org/ --with-build-config=bootstrap-lto --with-linker-hash-style=gnu --with-system-zlib --enable-__cxa_atexit --enable-cet=auto --enable-checking=release --enable-clocale=gnu --enable-default-pie --enable-default-ssp --enable-gnu-indirect-function --enable-gnu-unique-object --enable-libstdcxx-backtrace --enable-link-serialization=1 --enable-linker-build-id --enable-lto --enable-multilib --enable-plugin --enable-shared --enable-threads=posix --disable-libssp --disable-libstdcxx-pch --disable-werror
Thread model: posix
Supported LTO compression algorithms: zlib zstd
gcc version 12.2.1 20230111 (GCC) 
COLLECT_GCC_OPTIONS='-v' '-m32' '-I' '../include' '-o' 'main.out' '-e' 'kernel_init' '-nostartfiles' '-mtune=generic' '-march=x86-64' '-dumpdir' 'main.out-'
 /usr/lib/gcc/x86_64-pc-linux-gnu/12.2.1/cc1 -quiet -v -I ../include -imultilib 32 main.c -quiet -dumpdir main.out- -dumpbase main.c -dumpbase-ext .c -m32 -mtune=generic -march=x86-64 -version -o /tmp/ccGnztY6.s
GNU C17 (GCC) version 12.2.1 20230111 (x86_64-pc-linux-gnu)
        compiled by GNU C version 12.2.1 20230111, GMP version 6.2.1, MPFR version 4.2.0, MPC version 1.3.1, isl version isl-0.25-GMP

GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
ignoring nonexistent directory "/usr/lib/gcc/x86_64-pc-linux-gnu/12.2.1/../../../../x86_64-pc-linux-gnu/include"
#include "..." search starts here:
#include <...> search starts here:
 ../include
 /usr/lib/gcc/x86_64-pc-linux-gnu/12.2.1/include
 /usr/local/include
 /usr/lib/gcc/x86_64-pc-linux-gnu/12.2.1/include-fixed
 /usr/include
End of search list.
GNU C17 (GCC) version 12.2.1 20230111 (x86_64-pc-linux-gnu)
        compiled by GNU C version 12.2.1 20230111, GMP version 6.2.1, MPFR version 4.2.0, MPC version 1.3.1, isl version isl-0.25-GMP

GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
Compiler executable checksum: c5620313e3defc07ff561cb90de48ddc
COLLECT_GCC_OPTIONS='-v' '-m32' '-I' '../include' '-o' 'main.out' '-e' 'kernel_init' '-nostartfiles' '-mtune=generic' '-march=x86-64' '-dumpdir' 'main.out-'
 as -v -I ../include --32 -o /tmp/cc7mVQeo.o /tmp/ccGnztY6.s
GNU assembler version 2.40 (x86_64-pc-linux-gnu) using BFD version (GNU Binutils) 2.40
COMPILER_PATH=/usr/lib/gcc/x86_64-pc-linux-gnu/12.2.1/:/usr/lib/gcc/x86_64-pc-linux-gnu/12.2.1/:/usr/lib/gcc/x86_64-pc-linux-gnu/:/usr/lib/gcc/x86_64-pc-linux-gnu/12.2.1/:/usr/lib/gcc/x86_64-pc-linux-gnu/
LIBRARY_PATH=/usr/lib/gcc/x86_64-pc-linux-gnu/12.2.1/32/:/usr/lib/gcc/x86_64-pc-linux-gnu/12.2.1/../../../../lib32/:/lib/../lib32/:/usr/lib/../lib32/:/usr/lib/gcc/x86_64-pc-linux-gnu/12.2.1/:/usr/lib/gcc/x86_64-pc-linux-gnu/12.2.1/../../../:/lib/:/usr/lib/
COLLECT_GCC_OPTIONS='-v' '-m32' '-I' '../include' '-o' 'main.out' '-e' 'kernel_init' '-nostartfiles' '-mtune=generic' '-march=x86-64' '-dumpdir' 'main.out.'
 /usr/lib/gcc/x86_64-pc-linux-gnu/12.2.1/collect2 -plugin /usr/lib/gcc/x86_64-pc-linux-gnu/12.2.1/liblto_plugin.so -plugin-opt=/usr/lib/gcc/x86_64-pc-linux-gnu/12.2.1/lto-wrapper -plugin-opt=-fresolution=/tmp/cchxqz5t.res -plugin-opt=-pass-through=-lgcc -plugin-opt=-pass-through=-lgcc_s -plugin-opt=-pass-through=-lc -plugin-opt=-pass-through=-lgcc -plugin-opt=-pass-through=-lgcc_s --build-id --eh-frame-hdr --hash-style=gnu -m elf_i386 -dynamic-linker /lib/ld-linux.so.2 -pie -o main.out -e kernel_init -L/usr/lib/gcc/x86_64-pc-linux-gnu/12.2.1/32 -L/usr/lib/gcc/x86_64-pc-linux-gnu/12.2.1/../../../../lib32 -L/lib/../lib32 -L/usr/lib/../lib32 -L/usr/lib/gcc/x86_64-pc-linux-gnu/12.2.1 -L/usr/lib/gcc/x86_64-pc-linux-gnu/12.2.1/../../.. /tmp/cc7mVQeo.o -lgcc --push-state --as-needed -lgcc_s --pop-state -lc -lgcc --push-state --as-needed -lgcc_s --pop-state
COLLECT_GCC_OPTIONS='-v' '-m32' '-I' '../include' '-o' 'main.out' '-e' 'kernel_init' '-nostartfiles' '-mtune=generic' '-march=x86-64' '-dumpdir' 'main.out.'
```
**编译过程由 cc1 完成**


# 15 
- 出现  PKGBUILD contains CRLF characters and cannot be sourced. 问题
把 vscode 下方 CRLF 改为 LF
- 出现 SDL.h
pacman -S sdl

.PHONY
因为是根据时间生成的


branch 35 | 安装声卡驱动
以下有一些可能没有必要安装，也不管什么全部安装后重启一下系统就可以了。
sudo pacman -S alsa-utils
sudo pacman -S alsa-plugins
sudo pacman -S pulseaudio-alsa
sudo pacman -S pavucontrol-qt
sudo pacman -S pavucontrol
启用：amixer sset Master unmute



## 48
yield()系统调用，进程主动交出执行权，调度执行其他进程