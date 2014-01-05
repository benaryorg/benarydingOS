#include "../header.h"

/*
 * void idt_entry_set(int i,unsigned int base,unsigned int limit,int flags)
{
	uint64_t entry=0;
	entry|=limit&0xffffLL;
	entry|=(base&0xffffffLL)<<16;
	entry|=(flags&0xffLL)<<40;
	entry|=((limit>>16)&0xfLL)<<48;
	entry|=((flags>>8)&0xffLL)<<52;
	entry|=((base>>24)&0xffLL)<<56;
	*idt_func(i)=entry;
}
*/

uint64_t idt_entry_get(int i)
{
	return *idt_func(i);
}

uint64_t *idt_func(int i)
{
	static uint64_t idt[IDT_SIZE]={};
	
	return idt+i;
}

void idt_init(void)
{
	struct
	{
		uint16_t limit;
		void *ptr;
	}
	__attribute__((packed)) idtptr=
	{
		.limit=IDT_SIZE*8-1,
		.ptr=idt_func(0),
	};

	asm volatile("lidt %0" : : "m" (idtptr));
	idt_reload();
}

void idt_reload(void)
{
	asm volatile
	(
		"mov $0x10, %ax\n"
		"mov %ax, %ds\n"
		"mov %ax, %es\n"
		"mov %ax, %fs\n"
		"mov %ax, %gs\n"
		"mov %ax, %ss\n"
		"ljmp $0x8, $.1\n"
		".1:\n"
	); 
}
