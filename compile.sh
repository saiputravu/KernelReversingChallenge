#!/bin/bash
rm src/obj/*
nasm -f elf32 src/start.asm -o src/obj/start.o
for i in `ls src | egrep .c$`; do gcc -m32 -c src/$i -o src/obj/$i.o -ffreestanding -O -masm=intel ;done
ld -m elf_i386 -T src/linker.ld -o bin/mykernel src/obj/*.o

# Building the .iso file
grub-file --is-x86-multiboot bin/mykernel
mkdir -p isodir/boot/grub
cp bin/mykernel isodir/boot/mykernel
cp src/grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o myOS.iso isodir/

