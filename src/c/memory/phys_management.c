#include "../header.h"

void free(void *ptr)
{
	physmemrmalloc(ptr);
}

void *malloc(size_t size)
{
	size_t i,j;
	mem_allocated_t tile;
	mem_allocated_t *tmp;
	for(i=0;i<MEM_STACK_SIZE;i++)
	{
		if((tmp=physmemgetallocation(i))->start)
		{
			tile.start=tmp->end+1;
			tile.end=tile.start+size;
			for(j=0;j<MEM_STACK_SIZE;j++)
			{
				if((tmp=physmemgetallocation(j))->start)
				{
					if((tmp->start<=tile.end&&tmp->start>=tile.start)||(tmp->end<=tile.end&&tmp->end>=tile.start))
					{
						break;
					}
				}
			}
			if(j>=MEM_STACK_SIZE)
			{
				physmemsetallocation(&tile);
				return tile.start;
			}
		}
	}
	return 0;
}

void physmeminit(multiboot_info_t *mb_info)
{
	multiboot_mmap_t *mmap=mb_info->mbs_mmap_addr;
	multiboot_mmap_t *map_end=(void*)((uintptr_t) mb_info->mbs_mmap_addr + mb_info->mbs_mmap_length);
	mem_allocated_t addr;
	while(mmap<map_end)
	{
		if(mmap->Type!=MEM_FREE)
		{
			addr.start=(void *)mmap->BaseAddr;
			addr.end=addr.start+mmap->Length;
			physmemsetallocation(&addr);
		}
		mmap++;
	}
	addr.start=(void *)&_KERNEL_START;
	addr.end=(void *)&_KERNEL_END;
	physmemsetallocation(&addr);
}

void physmemsetallocation(mem_allocated_t *tile)
{
	size_t i;
	for(i=0;i<MEM_STACK_SIZE;i++)
	{
		if(!(physmemgetallocation(i)->start))
		{
			phys_mem_allocation(i,tile,1);
			break;
		}
	}
}

void physmemrmalloc(void *ptr)
{
	if(ptr)
	{
		size_t i;
		for(i=0;i<MEM_STACK_SIZE;i++)
		{
			if(physmemgetallocation(i)->start==ptr)
			{
				mem_allocated_t tile;
				tile.start=0;
				tile.end=0;
				phys_mem_allocation(i,&tile,1);
				break;
			}
		}
	}
}

mem_allocated_t *physmemgetallocation(size_t i)
{
	return phys_mem_allocation(i,0,0);
}

mem_allocated_t *phys_mem_allocation(size_t i,mem_allocated_t *tile,char set)
{
	static mem_allocated_t stack[MEM_STACK_SIZE];
	if(set)
	{
		stack[i].start=tile->start;
		stack[i].end=tile->end;
	}
	else
	{
		return stack+i;
	}
	return 0;
}
