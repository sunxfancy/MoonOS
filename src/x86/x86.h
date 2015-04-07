/*
* @Author: sxf
* @Date:   2015-04-07 09:46:36
* @Last Modified by:   sxf
* @Last Modified time: 2015-04-07 16:28:36
*/

#ifndef X86_H
#define X86_H

#include "../stddef.h"

#define IDTSIZE		0xFF
#define GDTSIZE		0xFF

#define IDTBASE		0x00000000
#define GDTBASE		0x00000800

#define	KERNEL_PDIR			0x00001000
#define	KERNEL_STACK		0x0009FFF0
#define	KERNEL_BASE			0x00100000
#define KERNEL_PG_HEAP		0x00800000
#define KERNEL_PG_HEAP_LIM	0x10000000
#define KERNEL_HEAP			0x10000000
#define KERNEL_HEAP_LIM		0x40000000

#define	USER_OFFSET 		0x40000000
#define	USER_STACK 			0xE0000000

#define PAGE(addr)		(addr) >> 12


// 全局描述符表 GDT中的一项, 整体为64位
struct _gdtdesc {
	uint16_t lim0_15;
	uint16_t base0_15;
	uint8_t base16_23;
	uint8_t acces;
	uint8_t lim16_19: 4;
	uint8_t other: 4;
	uint8_t base24_31;
} __attribute__ ((packed));
typedef struct _gdtdesc gdtdesc;


/* GDTR */
struct _gdtr {
	uint16_t limite;
	uint32_t base;
} __attribute__ ((packed));
typedef struct _gdtr gdtr;

struct _idtdesc {
	uint16_t offset0_15;
	uint16_t select;
	uint16_t type;
	uint16_t offset16_31;
} __attribute__ ((packed));
typedef struct _idtdesc idtdesc;

struct _idtr {
	uint16_t limite;
	uint32_t base;
} __attribute__ ((packed));
typedef struct _idtr idtr;

struct _tss {
	uint16_t previous_task, __previous_task_unused;
	uint32_t esp0;
	uint16_t ss0, __ss0_unused;
	uint32_t esp1;
	uint16_t ss1, __ss1_unused;
	uint32_t esp2;
	uint16_t ss2, __ss2_unused;
	uint32_t cr3;
	uint32_t eip, eflags, eax, ecx, edx, ebx, esp, ebp, esi, edi;
	uint16_t es, __es_unused;
	uint16_t cs, __cs_unused;
	uint16_t ss, __ss_unused;
	uint16_t ds, __ds_unused;
	uint16_t fs, __fs_unused;
	uint16_t gs, __gs_unused;
	uint16_t ldt_selector, __ldt_sel_unused;
	uint16_t debug_flag, io_map;
} __attribute__ ((packed));
typedef struct _tss tss;

struct _regs_t
{
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
	uint32_t ds, es, fs, gs;
	uint32_t which_int, err_code;
	uint32_t eip, cs, eflags, user_esp, user_ss;
} __attribute__((packed));
typedef struct _regs_t regs_t;

/** functions **/

void init_gdt_desc(gdtdesc *,uint32_t, uint32_t, uint8_t, uint8_t);
void init_gdt(void);
uint32_t cpu_vendor_name(char *name);

/*
void init_desc(gdtdesc *,uint32_t, uint8_t);
void init_idt_desc(idtdesc *,uint16_t, uint32_t, uint16_t );
void init_idt(void);
void init_pic(void);
*/




#endif // X86_H


