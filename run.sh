#!/bin/bash 
./compile.sh 
#qemu-system-i386 -cdrom myOS.iso -gdb tcp::6969
qemu-system-i386 -kernel bin/mykernel -gdb tcp::6969
