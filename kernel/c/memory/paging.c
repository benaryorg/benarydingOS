#include "header.h"

void paging_init(void)
{
	uint32_t cr0;
	int i;

	static page_context_t *kernel=0;
	kernel=page_mk_context();

	for(i=0;i<4096*1024;i+=0x1000)
	{
		page_map(kernel,(void *)i,(void *)i);
	}

	page_activate_context(kernel);

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

void page_activate_context(page_context_t *c)
{
	asm volatile("mov %0, %%cr3" : : "r" (c->pagedir));
}

void page_map(page_context_t *c,void *virt,void *phys)
{
	int i=(int)((uint32_t)phys/4096);
	if(!c->pagedir[i/1024])
	{
		c->pagedir[i/1024]=(uint32_t)physmalloc(4096);
		memset((void *)c->pagedir[i/1024],0,4096);
	}
	((uint32_t *)c->pagedir[i/1024])[1%1024]=((uint32_t)phys)|PTE_PRESENT|PTE_WRITE;
	asm volatile("invlpg %0" : : "m" (*(char*)virt));
}
