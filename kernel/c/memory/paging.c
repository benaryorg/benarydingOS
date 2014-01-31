#include "header.h"

void paging_init(void)
{
	uint32_t cr0;
	asm volatile("mov %%cr0, %0" : "=r" (cr0));
	cr0 |= (1 << 31);
	asm volatile("mov %0, %%cr0" : : "r" (cr0));
}

page_context_t *page_mk_context(void)
{
	page_context_t *c=physmalloc(4096);
	memset(c,0,4096);
	return c;
}

void vmm_map_page(page_context_t *c,void *virt,void *phys)
{
	int i=(int)((uint64_t)phys/4096);
}
