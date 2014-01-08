#include "../header.h"

void gdt_entry_set(int i,unsigned int base,unsigned int limit,int flags)
{
	uint64_t entry=0;
	entry|=limit&0xffffLL;
	entry|=(base&0xffffffLL)<<16;
	entry|=(flags&0xffLL)<<40;
	entry|=((limit>>16)&0xfLL)<<48;
	entry|=((flags>>8)&0xffLL)<<52;
	entry|=((base>>24)&0xffLL)<<56;
	*gdt_func(i)=entry;
}

uint64_t gdt_entry_get(int i)
{
	return *gdt_func(i);
}

uint64_t *gdt_func(int i)
{
	static uint64_t gdt[GDT_SIZE]={};
	
	return gdt+i;
}

void gdt_init(void)
{
	gdt_entry_set(0,0,0,0);
	gdt_entry_set(1,0,0xfffff,GDT_FLAG_SEGMENT|GDT_FLAG_32_BIT|GDT_FLAG_CODESEG|GDT_FLAG_4K_GRAN|GDT_FLAG_PRESENT);
	gdt_entry_set(2,0,0xfffff,GDT_FLAG_SEGMENT|GDT_FLAG_32_BIT|GDT_FLAG_DATASEG|GDT_FLAG_4K_GRAN|GDT_FLAG_PRESENT);
	gdt_entry_set(3,0,0xfffff,GDT_FLAG_SEGMENT|GDT_FLAG_32_BIT|GDT_FLAG_CODESEG|GDT_FLAG_4K_GRAN|GDT_FLAG_PRESENT|GDT_FLAG_RING3);
	gdt_entry_set(4,0,0xfffff,GDT_FLAG_SEGMENT|GDT_FLAG_32_BIT|GDT_FLAG_DATASEG|GDT_FLAG_4K_GRAN|GDT_FLAG_PRESENT|GDT_FLAG_RING3);
	gdt_entry_set(5,(uint32_t)tss_func(0),sizeof(uint32_t)*TSS_SIZE,GDT_FLAG_TSS|GDT_FLAG_PRESENT/*|GDT_FLAG_RING3*/);

	struct
	{
		uint16_t limit;
		void *ptr;
	}
	__attribute__((packed)) gdtptr=
	{
		.limit=GDT_SIZE*8-1,
		.ptr=gdt_func(0),
	};

	asm volatile("lgdt %0" : : "m" (gdtptr));
	asm volatile("ltr %%ax" : : "a" (5 << 3));
	register_reload();
}
