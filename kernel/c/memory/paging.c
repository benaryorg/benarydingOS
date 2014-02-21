#include "header.h"

void paging_init(void)
{
	static page_context_t *kernel_ctx;

	uint32_t cr0;
	int i;

	kernel_ctx=page_mk_context();

	for(i=0x1000;i<4*1024*1024;i+=0x1000)
	{
		page_map(kernel_ctx,i,i,PTE_PRESENT|PTE_WRITE);
	}
	page_activate_context(kernel_ctx);

	asm volatile("mov %%cr0, %0" : "=r" (cr0));
	cr0|=(1<<31);
	asm volatile("mov %0, %%cr0" : : "r" (cr0));
}

page_context_t *page_mk_context(void)
{
	page_context_t *c=physmallocblock();//(sizeof(page_context_t));
	page_map(c,(uint32_t)c,(uint32_t)c,PTE_PRESENT|PTE_WRITE);
	c->pagedir=(uint32_t *)physmallocblock();
	memset(c->pagedir,0,4096);
	page_map(c,(uint32_t)c->pagedir,(uint32_t)c->pagedir,PTE_PRESENT|PTE_WRITE);
	return c;
}

void page_activate_context(page_context_t *c)
{
	asm volatile("mov %0, %%cr3" : :  "r" (c->pagedir));
}

void page_map(page_context_t *c,uint32_t virt,uint32_t phys,uint32_t flags)
{
	if(!virt||(phys&0x1))
	{
		kernelpanic("Evil Flags!");
		return;
	}
	int i=virt/4096;
	uint32_t *pagetable=(uint32_t *)(c->pagedir+(i/1024));
	if(!*pagetable)
	{
		*pagetable=(uint32_t)physmallocblock();
		memset((void *)*pagetable,0,4096);
        page_map(c,*pagetable,*pagetable,PTE_PRESENT|PTE_WRITE);
	}
	((uint32_t *)*pagetable)[i%1024]=phys|flags;
	asm volatile("invlpg %0" : : "m" (*(char*)virt));
}
