#include "header.h"

void *mallocblocks(page_context_t *c,int blocks)
{
    if(blocks>1024)
    {
        return 0;
    }
    char tmp=0;
    int i,j,k;
    for(i=0x200;i<0x10000;i++)
    {
        if(((uint32_t)c->pagedir[i/1024])&1)
        {
            for(j=0;j<1024-blocks;j++)
            {
                for(k=0;k<blocks&&tmp;k++)
                {
                    if(((uint32_t)c->pagedir[i/1024][j+k])&1)
                    {
                        tmp=1;
                    }
                }
                if(!k)
                {
                    for(k=0;k<blocks&&tmp;k++)
                    {
                        page_map(c,(uint32_t)((i*1024+j+k)*4096),(uint32_t)physmallocblock(),PTE_PRESENT|PTE_WRITE);
                    }
                    return c->pagedir[i/1024][j+k];
                }
            }
        }
    }
    for(i=0x200;1;i++)
    {
        if(!(((uint32_t)c->pagedir[i/1024])&1))
        {
            c->pagedir[i/1024]=(pagetable_t)(((uint32_t)physmallocblock())|PTE_PRESENT);
            page_map(c,(uint32_t)c->pagedir[i/1024]&~0xFFF,(uint32_t)c->pagedir[i/1024]&~0xFFF,PTE_PRESENT|PTE_WRITE);
            for(k=0;k<blocks&&tmp;k++)
            {
                page_map(c,(uint32_t)((i*1024+k)*4096),(uint32_t)physmallocblock(),PTE_PRESENT|PTE_WRITE);
            }
            return c->pagedir[i/1024][k];
        }
    }
    return 0;
}
