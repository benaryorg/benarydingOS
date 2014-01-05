#include "../header.h"

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
