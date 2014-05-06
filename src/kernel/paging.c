#include "header.h"

/**
 * Initialise paging
 * TODO comment
 *
 * @return First and basic paging context
 */
page_context_t *paging_init(void)
{
	static page_context_t *kernel_ctx;

	uint32_t cr0;
	int i;

	kernel_ctx=page_mk_context(1);

	for(i=1;i<0x1000;i++)
	{
		page_map(kernel_ctx,i<<12,i<<12,PTE_PRESENT|PTE_WRITE|(((i<0x200)?1<<9:0)));
	}
	page_map(kernel_ctx,(uint32_t)kernel_ctx,(uint32_t)kernel_ctx,PTE_PRESENT|PTE_WRITE|(1<<9));
	page_map(kernel_ctx,(uint32_t)kernel_ctx->pagedir,(uint32_t)kernel_ctx->pagedir,PTE_PRESENT|PTE_WRITE|(1<<9));
	for(i=0;i<2;i++)
	{
		page_map(kernel_ctx,(0xB8+i)*0x1000,(0xB8+i)*0x1000,PTE_PRESENT|PTE_WRITE|(1<<9));
	}
	page_activate_context(kernel_ctx);

	asm volatile("mov %%cr0, %0" : "=r" (cr0));
	cr0|=(1<<31);
	asm volatile("mov %0, %%cr0" : : "r" (cr0));

	return kernel_ctx;
}

/**
 * Create a basic paging context
 * TODO comment
 *
 * @param use_phys Tells if physical addresses should be used
 * @return the context
 */
page_context_t *page_mk_context(char use_phys)
{
	page_context_t *c=physmallocblock();//(sizeof(page_context_t));
	page_map(c,(uint32_t)c,(uint32_t)c,PTE_PRESENT|PTE_WRITE);
	if(use_phys)
	{
		c->pagedir=(pagedir_t)physmallocblock();
		page_map(c,(uint32_t)c->pagedir,(uint32_t)c->pagedir,PTE_PRESENT|PTE_WRITE);
	}
	else
	{
		c->pagedir=(pagedir_t)mallocblocks(c,1);
	}
	memset(c->pagedir,0,4096);
	return c;
}

/**
 * Activates the context
 *
 * @param c Context to activate
 */
void page_activate_context(page_context_t *c)
{
	asm volatile("movl %0, %%cr3" : :  "r" (c->pagedir));
}

/**
 * Invalidate page at virtual address virt to prevent caching
 *
 * @param virt Address of page to invalidate
 */
void invalpage(uint32_t virt)
{
	asm volatile("invlpg %0" : : "m" (*(char *)virt));
}

/**
 * Map a page into context
 * TODO comment
 *
 * @param c pageing context
 * @param virt Virtual address to map to
 * @param phys Physical address to map
 * @param flags The flags to use
 */
void page_map(page_context_t *c,uint32_t virt,uint32_t phys,uint32_t flags)
{
//	printf("Map p%x to v%x\n",phys,virt);
	if(!virt||((virt|phys)&0xFFF))
	{
		resetcolor();
		printf("ctx:%x\npd:%x\nv:%x\np:%x\n",(unsigned)c,(unsigned)c->pagedir,(unsigned)virt,(unsigned)phys);
		kernelpanic("Evil Flags!");
		return;
	}
	int i=virt>>12;
	if(!(((uint32_t)c->pagedir[i/1024])&0xFFF))
	{
		c->pagedir[i/1024]=(pagetable_t)(((uint32_t)physmallocblock())|PTE_PRESENT);
		page_map(c,(uint32_t)c->pagedir[i/1024]&~0xFFF,(uint32_t)c->pagedir[i/1024]&~0xFFF,PTE_PRESENT|PTE_WRITE);
		memset((void *)(((uint32_t)c->pagedir[i/1024])&~0xFFF),0,4096);
	}
	pagetable_t table=(pagetable_t)(((uint32_t)c->pagedir[i/1024])&~0xFF);
	table[i%1024]=(uint32_t *)(phys|flags);
	invalpage(virt);
}
