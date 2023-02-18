# README

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