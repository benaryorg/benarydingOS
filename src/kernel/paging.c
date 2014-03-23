#include "header.h"

void paging_init(void)
{
    static page_context_t *kernel_ctx;

    uint32_t cr0;
    int i;

    kernel_ctx=page_mk_context(1); //is blocking HERE!

    for(i=0x1000;i<4*1024*1024;i+=0x1000)
    {
        page_map(kernel_ctx,i,i,PTE_PRESENT|PTE_WRITE);
    }
    page_map(kernel_ctx,(uint32_t)kernel_ctx,(uint32_t)kernel_ctx,PTE_PRESENT|PTE_WRITE);
//    page_map(kernel_ctx,(uint32_t)kernel_ctx->pagedir,(uint32_t)kernel_ctx->pagedir,PTE_PRESENT|PTE_WRITE);
    for(i=0;i<2;i++)
    {
        page_map(kernel_ctx,(0xB8+i)*0x1000,(0xB8+i)*0x1000,PTE_PRESENT|PTE_WRITE);
    }
    page_activate_context(kernel_ctx);

    asm volatile("mov %%cr0, %0" : "=r" (cr0));
    cr0|=(1<<31);
    asm volatile("mov %0, %%cr0" : : "r" (cr0));
}

page_context_t *page_mk_context(char use_phys)
{
    page_context_t *c=physmallocblock();//(sizeof(page_context_t));
    if(use_phys)
    {
        c->pagedir=(pagedir_t)physmallocblock();
        page_map(c,(uint32_t)c,(uint32_t)c,PTE_PRESENT|PTE_WRITE);
    }
    else
    {
        c->pagedir=(pagedir_t)mallocblocks(c,1);
    }
    memset(c->pagedir,0,4096);
    return c;
}

void page_activate_context(page_context_t *c)
{
    asm volatile("movl %0, %%cr3" : :  "r" (c->pagedir));
}

void invalpage(uint32_t virt)
{
    asm volatile("invlpg %0" : : "m" (*(char *)virt));
}

void page_map(page_context_t *c,uint32_t virt,uint32_t phys,uint32_t flags)
{
    if(!virt||((virt|phys)&0xFFF))
    {
        printf("ctx:%x\npd:%x\nv:%x\np:%x\n",(unsigned)c,(unsigned)c->pagedir,(unsigned)virt,(unsigned)phys);
        kernelpanic("Evil Flags!");
        return;
    }
    int i=virt>>12;
    if(!(((uint32_t)c->pagedir[i/1024])&0xFFF))
    {
        c->pagedir[i/1024]=(pagetable_t)(((uint32_t)mallocblocks(c,1))|PTE_PRESENT);
//        page_map(c,(uint32_t)c->pagedir[i/1024]&~0xFFF,(uint32_t)c->pagedir[i/1024]&~0xFFF,PTE_PRESENT|PTE_WRITE);
        memset((void *)c->pagedir[i/1024],0,4096);
    }
    pagetable_t table=(pagetable_t)(((uint32_t)c->pagedir[i/1024])&~0xFF);
    table[i%1024]=(uint32_t *)(phys|flags);
    invalpage(virt);
}
