#include "../header.h"

void tss_init(void)
{
	gdt_entry_set(5,(uint32_t)tss_func(0),sizeof(uint32_t)*TSS_SIZE,GDT_FLAG_TSS|GDT_FLAG_PRESENT|GDT_FLAG_RING3);
	asm volatile("ltr %%ax" : : "a" (5 << 3));
	register_reload();
}

void tss_entry_set(int i,uint32_t data)
{
	*tss_func(i)=data;
}

uint32_t tss_entry_get(int i)
{
	return *tss_func(i);
}

uint32_t *tss_func(int i)
{
	static uint32_t tss[TSS_SIZE]={0,0,0x10};

	return tss+i;
}
