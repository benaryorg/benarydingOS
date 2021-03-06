#include "header.h"

/**
 * Physical free
 *
 * @param ptr address to free
 */
void physfree(void *ptr)
{
	physmemrmalloc(ptr);
}

/**
 * Get last possible address
 *
 * @return address
 */
void *getramsize(void)
{
	return ram_size_func(0);
}

/**
 * Set last possible address
 *
 * @param ptr Address to set
 */
void setramsize(void *ptr)
{
	ram_size_func(ptr);
}

/**
 * Internal function for this pointer (DO NOT USE)
 *
 * @param ptr set if not 0
 * @return return ramsize
 */
void *ram_size_func(void *ptr)
{
	static void *ramsize=0;
	if(ptr)
	{
		ramsize=ptr;
	}
	return ramsize;
}

/**
 * Allocate one block
 * TODO comment
 *
 * @return the address of the block
 */
void *physmallocblock(void)
{
	static uint32_t last=0;
	uint32_t i;
	int j;
	mem_allocation_t tile;
	mem_allocation_t *tmp;
	for(i=last+0x1000;i!=last;i+=0x1000)
	{
		if(i>0x180000)//tile.end>=getramsize()) TODO
		{
			i=0;
		}
		tile.start=(void *)i;
		tile.end=tile.start+4096;
		for(j=0;j<MEM_STACK_SIZE;j++)
		{
			if((tmp=physmemgetallocation(j))->start)
			{
				if(!((tmp->end<tile.start&&tmp->start<tile.start)||(tmp->start>=tile.end&&tmp->end>=tile.end)))
				{
					break;
				}
			}
		}
		if(j>=MEM_STACK_SIZE)
		{
			last=i;
			physmemsetallocation(&tile);
			return tile.start;
		}
	}
	return 0;
}

/**
 * Allocate size block
 * TODO comment
 *
 * @param size count of blocks
 * @return the address of the first block
 */
void *physmalloc(unsigned int size)
{
//	static int last=0;
	int i,j;
	mem_allocation_t tile;
	mem_allocation_t *tmp;
	for(i=MEM_STACK_SIZE;i>=0;i--)
//	for(i=0;i<MEM_STACK_SIZE;i++) TODO
	{
		if(((tmp=physmemgetallocation(i))->start))
		{
			tile.start=tmp->end+1;
			tile.end=tile.start+size-1;
			if(0)//tile.end>getramsize()) TODO
			{
				printf("%p/%p\n",getramsize,tile.end);
				break;
			}
			for(j=0;j<MEM_STACK_SIZE;j++)
			{
				if((tmp=physmemgetallocation(j))->start)
				{
					if(!((tmp->end<tile.start&&tmp->start<tile.start)||(tmp->start>=tile.end&&tmp->end>=tile.end)))
					{
						break;
					}
				}
			}
			if(j>=MEM_STACK_SIZE)
			{
//				last=i;
				physmemsetallocation(&tile);
				return tile.start;
			}
		}
	}
	return 0;
}

/**
 * Initialize physical memory
 * TODO comment
 * 
 * @param mb_info multiboot structure
 */
void physmeminit(multiboot_info_t *mb_info)
{
	cpu_state_t *cpu;
    page_context_t *c;
	task_t *task;
	mem_allocation_t addr;
	addr.start=addr.end=0;

	addr.end=(void *)&_KERNEL_END;
	printf("\nKernel End: %p\n",addr.end);
	physmemsetallocation(&addr);

	addr.start=BUFFER_TEXT;
	addr.end=addr.start+BUFFER_TEXT_WIDTH*BUFFER_TEXT_HEIGHT;
	physmemsetallocation(&addr);

	multiboot_module_t *modules=(multiboot_module_t *)mb_info->mbs_mods_addr;
	addr.start=mb_info;
	addr.end=(char *)addr.start+4096;
	physmemsetallocation(&addr);
	addr.start=modules;
	addr.end=(char *)addr.start+4096;
	physmemsetallocation(&addr);
	int i,j;
	multiboot_mmap_t *mmap=(multiboot_mmap_t *)mb_info->mbs_mmap_addr;
	multiboot_mmap_t *map_end=(multiboot_mmap_t *)((uintptr_t)mb_info->mbs_mmap_addr+mb_info->mbs_mmap_length);
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
	for(i=0;i<mb_info->mbs_mods_count;i++)
	{
		printf("Module %d:\n",i);
		addr.start=(void *)modules[i].mod_start;
		addr.end=(void *)modules[i].mod_end;
		size_t length=addr.end-addr.start;
		physmemsetallocation(&addr);
		puts("\tOld Memory allocated");
		void *load_addr=(void *)(0x100000*(i+2));
		memcpy(load_addr,addr.start,length);
		puts("\tModule copied");
		addr.start=load_addr;
		addr.end=addr.start+length;
		physmemsetallocation(&addr);
		puts("\tNew Memory allocated");
		c=page_mk_context(1);
        task=mallocblocks(c,1);
        task->context=c;
		for(i=0x1000;i<4*1024*1024;i+=0x1000)
		{
			page_map(task->context,i,i,PTE_PRESENT|(1<<9));
		}
		for(j=0;j<0x50;j+=0x1)
		{
			page_map(task->context,((uint32_t)load_addr)+(j*0x5000),0x200000+(j*0x5000),PTE_PRESENT|PTE_WRITE|(1<<9));
		}
		cpu=cpu_new(task->context,load_addr,0);
		task->id=0;
		task->cpu=cpu;
		task_schedule(task);
		puts("\tNew Task added\n");
	}
}

/**
 * Set an allocation from tile.start to tile.end
 *
 * @param tile the tile to allocate
 */
void physmemsetallocation(mem_allocation_t *tile)
{
	size_t i;
	for(i=0;i<MEM_STACK_SIZE;i++)
	{
		if(!(physmemgetallocation(i)->start))
		{
			if(!tile->start)
			{
				tile->start+=1;
				phys_mem_allocation(i,tile,1);
				tile->start-=1;
			}
			else
			{
				phys_mem_allocation(i,tile,1);
			}
			break;
		}
	}
}

/**
 * Remove allocations at ptr
 *
 * @param ptr The pointer to the start of the allocation to remove
 */
void physmemrmalloc(void *ptr)
{
	size_t i;
	for(i=0;i<MEM_STACK_SIZE;i++)
	{
		if(physmemgetallocation(i)->start==ptr)
		{
			mem_allocation_t tile;
			tile.start=0;
			tile.end=0;
			phys_mem_allocation(i,&tile,1);
			break;
		}
	}
}

/**
 * Get ith allocation
 *
 * @param i What tile
 * @return "Allocation Tile"
 */
mem_allocation_t *physmemgetallocation(size_t i)
{
	return phys_mem_allocation(i,0,0);
}

/**
 * Backend for allocated tiles (DO NOT USE)
 *
 * @param i tile to set/return
 * @param tile tile to set entry to
 * @param set if not 0 tile is set else returned
 * @return if set is 0 then returns the pointer to the tile in the array else 0
 */
mem_allocation_t *phys_mem_allocation(size_t i,mem_allocation_t *tile,char set)
{
	static mem_allocation_t stack[MEM_STACK_SIZE];
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
