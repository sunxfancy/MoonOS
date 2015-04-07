CC = gcc
ASM = nasm
LINK = ld

LINK_FLAG = -m elf_i386 -T ../link.ld 
CC_FLAG=  -m32 -c -fno-stack-protector
ASM_FLAG =  -f elf32
