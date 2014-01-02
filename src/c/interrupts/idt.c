#include "../header.h"

void set_idt_entry(int i,unsigned int base,unsigned int limit,int flags)
{
	idt[i]=limit&0xffffLL;
	idt[i]|=(base&0xffffffLL)<<16;
	idt[i]|=(flags&0xffLL)<<40;
	idt[i]|=((limit>>16)&0xfLL)<<48;
	idt[i]|=((flags>>8)&0xffLL)<<52;
	idt[i]|=((base>>24)&0xffLL)<<56;
}

void load_idt(void)
{
	struct
	{
		uint16_t limit;
		void* pointer;
	}
	__attribute__((packed)) idtp=
	{
		.limit=IDT_ENTRIES*8-1,
		.pointer=idt,
	};

	asm volatile("lidt %0" : : "m" (idtp));
}

void init_idt(void)
{
	set_idt_entry(0, 0, 0, 0);
	set_idt_entry(1, 0, 0xfffff, IDT_FLAG_SEGMENT | IDT_FLAG_32_BIT |
	IDT_FLAG_CODESEG | IDT_FLAG_4K_GRAN | IDT_FLAG_PRESENT);
	set_idt_entry(2, 0, 0xfffff, IDT_FLAG_SEGMENT | IDT_FLAG_32_BIT |
	IDT_FLAG_DATASEG | IDT_FLAG_4K_GRAN | IDT_FLAG_PRESENT);
	set_idt_entry(3, 0, 0xfffff, IDT_FLAG_SEGMENT | IDT_FLAG_32_BIT |
	IDT_FLAG_CODESEG | IDT_FLAG_4K_GRAN | IDT_FLAG_PRESENT | IDT_FLAG_RING3);
	set_idt_entry(4, 0, 0xfffff, IDT_FLAG_SEGMENT | IDT_FLAG_32_BIT |
	IDT_FLAG_DATASEG | IDT_FLAG_4K_GRAN | IDT_FLAG_PRESENT | IDT_FLAG_RING3);

	load_idt();
}
