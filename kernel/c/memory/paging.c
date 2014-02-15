#include "header.h"

#define KERNEL_PAGE_TABLES_VADDR 0x3fc00000
#define PGDIR_SHIFT 22

static page_context_t *kernel;

void paging_init(void)
{
	uint32_t cr0;
	int i;

	kernel=page_mk_context();

	for(i=0;i<4*1024*1024;i+=0x1000)
	{
		page_map(kernel,i,i);
	}
	page_map(kernel,(uint32_t)kernel,(uint32_t)kernel);
    
	page_activate_context(kernel);

	asm volatile("mov %%cr0, %0" : "=r" (cr0));
	cr0|=(1<<31);
	asm volatile("mov %0, %%cr0" : : "r" (cr0));
}

page_context_t *page_mk_context(void)
{
	page_context_t *c=physmalloc(sizeof(page_context_t));
	c->pagedir=(void *)(((uint32_t)physmallocblock())|PTE_PRESENT|PTE_WRITE);
	memset(c->pagedir,0,4096);
	page_map(c,(uint32_t)c->pagedir,(uint32_t)c->pagedir);
	return c;
}

void page_activate_context(page_context_t *c)
{
	asm volatile("mov %0, %%cr3" : : "r" (c->pagedir));
}

void page_map(page_context_t *c,uint32_t virt,uint32_t phys)
{
	int i=virt/4096;
	if(!virt||((virt|phys)&0xFFF))
	{
		for(i=0;i<10000000;i++);
		putchar('#');
		return;
	}
	uint32_t *pagetable=(uint32_t *)(c->pagedir+(i/1024));
	if(!*pagetable)
	{
		*pagetable=(uint32_t)physmallocblock();
		memset((void *)*pagetable,0,4096);
        *pagetable|=PTE_PRESENT|PTE_WRITE;
        page_map(c,*pagetable,*pagetable);
	}
	((uint32_t *)*pagetable)[i%1024]=phys|PTE_PRESENT|PTE_WRITE|0xFFF;
	asm volatile("invlpg %0" : : "m" (*(char*)virt));
}
