include ./src/$(arch)/config.make

include ./src/boot/makefile
include ./src/kernel/makefile
include ./src/$(arch)/makefile

OBJS := $(OBJS) kernel.o

vpath %.c src
vpath %.S src
vpath %.asm src

