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

