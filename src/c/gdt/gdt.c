#include "../header.h"

void set_gdt_entry(int i,unsigned int base,unsigned int limit,int flags)
{
	gdt[i]=limit&0xffffLL;
	gdt[i]|=(base&0xffffffLL)<<16;
	gdt[i]|=(flags&0xffLL)<<40;
	gdt[i]|=((limit>>16)&0xfLL)<<48;
	gdt[i]|=((flags>>8)&0xffLL)<<52;
	gdt[i]|=((base>>24)&0xffLL)<<56;
}

void load_gdt(void)
{
	struct
	{
		uint16_t limit;
		void* pointer;
	}
	__attribute__((packed)) gdtp=
	{
		.limit=GDT_ENTRIES*8-1,
		.pointer=gdt,
	};

	asm volatile("lgdt %0" : : "m" (gdtp));
}

void init_gdt(void)
{
	set_gdt_entry(0, 0, 0, 0);
	set_gdt_entry(1, 0, 0xfffff, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT |
	GDT_FLAG_CODESEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT);
	set_gdt_entry(2, 0, 0xfffff, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT |
	GDT_FLAG_DATASEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT);
	set_gdt_entry(3, 0, 0xfffff, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT |
	GDT_FLAG_CODESEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT | GDT_FLAG_RING3);
	set_gdt_entry(4, 0, 0xfffff, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT |
	GDT_FLAG_DATASEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT | GDT_FLAG_RING3);

	load_gdt();
}
