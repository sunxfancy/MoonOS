/* 
* @Author: sxf
* @Date:   2015-04-07 14:26:54
* @Last Modified by:   sxf
* @Last Modified time: 2015-04-07 16:59:54
*/
#include "x86.h"


void init_gdt_desc(gdtdesc *desc, uint32_t base, uint32_t limite, uint8_t acces, uint8_t other)
{
	desc->lim0_15 = (limite & 0xffff);
	desc->base0_15 = (base & 0xffff);
	desc->base16_23 = (base & 0xff0000) >> 16;
	desc->acces = acces;
	desc->lim16_19 = (limite & 0xf0000) >> 16;
	desc->other = (other & 0xf);
	desc->base24_31 = (base & 0xff000000) >> 24;
	return;
}

inline void initgd(gdtdesc *desc, uint32_t limite, uint8_t acces) {
	init_gdt_desc(desc, 0x0, limite, acces, 0x0D);
}

idtdesc* 	kidt; 		/* IDT table */
// intdesc* 	intt; 		/* Interruptions functions tables */
gdtdesc* 	kgdt;		/* GDT */
tss 		default_tss;
gdtr 		kgdtr;				/* GDTR */
// idtr 		kidtr; 				/* IDTR registry */

extern void printf(const char *format, ...);

void init_gdt() {
	default_tss.debug_flag = 0x00;
	default_tss.io_map = 0x00;
	default_tss.esp0 = 0x1FFF0;
	default_tss.ss0 = 0x18;	

	/* initialize gdt segments */
	kgdt = (gdtdesc*)GDTBASE;
	init_gdt_desc(&kgdt[0], 0x0, 0x0, 0x0, 0x0);
	initgd(&kgdt[1], 0xFFFFF, 0x9B);	/* code */
	initgd(&kgdt[2], 0xFFFFF, 0x93);	/* data */
	initgd(&kgdt[3], 0x0, 0x97);		/* stack */
	initgd(&kgdt[4], 0xFFFFF, 0xFF);	/* ucode */
	initgd(&kgdt[5], 0xFFFFF, 0xF3);	/* udata */
	initgd(&kgdt[6], 0x0, 0xF7);		/* ustack */
	init_gdt_desc(&kgdt[7], (uint32_t) &default_tss, 0x67, 0xE9, 0x00);	/* descripteur de tss */

	printf("gdt init done.\n");
}

void init_idt_desc(idtdesc *desc, uint16_t select, uint32_t offset, uint16_t type)
{
	desc->offset0_15 = (offset & 0xffff);
	desc->select = select;
	desc->type = type;
	desc->offset16_31 = (offset & 0xffff0000) >> 16;
	return;
}

inline void initid(gdtdesc *desc, uint32_t offset, uint16_t type) {
	init_idt_desc(desc, 0x08, offset, type);
}


void init_idt(void)
{
	kidt = (idtdesc*)IDTBASE;

	/* Init irq */
	int i;
	for (i = 0; i < IDTSIZE; i++)
		init_idt_desc(&kidt[i], 0x08, (uint32_t)_asm_schedule, INTGATE);
    /* Vectors  0 -> 31 are for exceptions */
    init_idt_desc(&kidt[13], 0x08, (uint32_t) _asm_exc_GP, INTGATE);	/* #GP */
    init_idt_desc(&kidt[14], 0x08, (uint32_t) _asm_exc_PF, INTGATE);	/* #PF */
    init_idt_desc(&kidt[15], 0x08, (uint32_t) _asm_schedule, INTGATE);
    init_idt_desc(&kidt[16], 0x08, (uint32_t) _asm_int_1, INTGATE);
    init_idt_desc(&kidt[17], 0x08, (uint32_t) _asm_syscalls, TRAPGATE);
    init_idt_desc(&kidt[18], 0x08, (uint32_t) _asm_syscalls, TRAPGATE); //48
    
    asm("lidtl (kidtr)");
}

regs_t cpu_cpuid(int code)
{
	regs_t r;
	asm volatile("cpuid":"=a"(r.eax),"=b"(r.ebx),
		"=c"(r.ecx),"=d"(r.edx):"0"(code));
	return r;
}


uint32_t cpu_vendor_name(char *name)
{
	regs_t r = cpu_cpuid(0x00);
	
	char line1[5];
	line1[0] = ((char *) &r.ebx)[0];
	line1[1] = ((char *) &r.ebx)[1];
	line1[2] = ((char *) &r.ebx)[2];
	line1[3] = ((char *) &r.ebx)[3];
	line1[4] = '\0';

	char line2[5];
	line2[0] = ((char *) &r.ecx)[0];
	line2[1] = ((char *) &r.ecx)[1];
	line2[2] = ((char *) &r.ecx)[2];
	line2[3] = ((char *) &r.ecx)[3];
	line2[4] = '\0';
	
	char line3[5];
	line3[0] = ((char *) &r.edx)[0];
	line3[1] = ((char *) &r.edx)[1];
	line3[2] = ((char *) &r.edx)[2];
	line3[3] = ((char *) &r.edx)[3];
	line3[4] = '\0';
						
	// strcpy(name, line1);
	// strcat(name, line3);
	// strcat(name, line2);
	return 15;
}
