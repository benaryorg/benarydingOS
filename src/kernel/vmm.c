#include "header.h"

/**
 * Allocate and map blocks
 * TODO comment
 * 
 * @param c context to map the blocks in
 * @param blocks how many blocks to map
 * @return the pointer to the first block (virtual address)
 */
void *mallocblocks(page_context_t *c,int blocks)
{
	if(blocks>1024)
	{
		return 0;
	}
	char tmp=0;
	int i,j,k;
	for(i=0x10;i<0x10000;i++)
	{
		if(((uint32_t)c->pagedir[i/1024])&1)
		{
			for(j=0;j<1024-blocks;j++)
			{
				for(tmp=k=0;k<blocks&&!tmp;k++)
				{
					if((((uint32_t)c->pagedir[i/1024][j+k])&((1<<9)|1))==((1<<9)|1))
					{
						tmp=1;
					}
				}
				if(!tmp)
				{
					for(k=0;k<blocks&&tmp;k++)
					{
						page_map(c,(uint32_t)((i*1024+j+k)<<12),(uint32_t)physmallocblock(),PTE_PRESENT|PTE_WRITE|(1<<9));
					}
//					printf("%x\n",c->pagedir[i/1024][j+k]);
					return (void *)((i*1024+j+k)<<12); //(void *)(((uint32_t)c->pagedir[i/1024][j+k])&~0xFFF);
				}
			}
		}
	}
	for(i=0x10;i<0x10000;i++)
	{
		if(!(((uint32_t)c->pagedir[i/1024])&1))
		{
			c->pagedir[i/1024]=(pagetable_t)(((uint32_t)physmallocblock())|PTE_PRESENT);
			page_map(c,((i<<10)<<12),((i<<10)<<12),PTE_PRESENT|PTE_WRITE);
/*		  
			{
				page_map(c,(uint32_t)((i*1024+j)<<12),(uint32_t)physmallocblock(),PTE_PRESENT|PTE_WRITE);
			}
*/
//			printf("%x\n",c->pagedir[i/1024]);
			return mallocblocks(c,blocks);
		}
	}
	return 0;
}
