target = moon
build_path = ./build
arch = x86

include ./src/makefile

all: iso

iso : $(target)
	mkisofs -o $(build_path)/$(target).iso  -b isolinux/isolinux.bin  -no-emul-boot  -boot-load-size 4  -boot-info-table  cdiso/

run : 
	qemu-system-i386 -kernel $(build_path)/$(target)

$(target) : $(OBJS)
	cd $(build_path) && $(LINK) $(LINK_FLAG) -o $(target) $^ 
	cp $(build_path)/$@ cdiso/$@

.PHONY : builddir 
builddir :
	-mkdir ./build

%.o : %.c  builddir
	$(CC) $(CC_FLAG) -o  $(build_path)/$@  $< 
	
%.o : %.S  builddir
	$(CC) $(CC_FLAG) -o  $(build_path)/$@  $<
	
%.o : %.asm  builddir
	$(ASM) $(ASM_FLAG) -o  $(build_path)/$@  $<

.PHONY : clean 
clean :
	-rm -rf $(build_path)