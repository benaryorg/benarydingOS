#include "../header.h"

void free(void *ptr)
{
	physmemrmalloc(ptr);
}

void *malloc(unsigned int size)
{
	static int last=0;
	int i,j;
	mem_allocation_t tile;
	mem_allocation_t *tmp;
	for(i=last+1;i!=last;i++)
	{
		if(i>MEM_STACK_SIZE)
		{
			i=-1;
			continue;
		}
		if(((tmp=physmemgetallocation(i))->start)&&tmp->start>&_KERNEL_END)
		{
			tile.start=tmp->end+1;
			tile.end=tile.start+size;
			for(j=0;j<MEM_STACK_SIZE;j++)
			{
				if((tmp=physmemgetallocation(j))->start)
				{
					if
					(
						(tmp->start>=tile.start && tmp->start<=tile.end)||
						(tmp->end>=tile.start && tmp->end<=tile.end)||
						(tmp->start<tile.start && tmp->end>tile.end)
					)
					{
						j=-1;
						break;
					}
				}
			}
			if(j!=-1)
			{
				last=i;
				physmemsetallocation(&tile);
				return tile.start;
			}
		}
	}
	return 0;
}

void physmeminit(multiboot_info_t *mb_info)
{
	mem_allocation_t addr;
	addr.start=addr.end=0;
	physmemsetallocation(&addr);

	multiboot_module_t *modules=(multiboot_module_t *)mb_info->mbs_mods_addr;
	addr.start=mb_info;
	addr.end=(char *)addr.start+4096;
	physmemsetallocation(&addr);
	addr.start=modules;
	addr.end=(char *)addr.start+4096;
	physmemsetallocation(&addr);
	int i;
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
	addr.start=(void *)&_KERNEL_START;
	addr.end=(void *)&_KERNEL_END;
	physmemsetallocation(&addr);
	for(i=0;i<mb_info->mbs_mods_count;i++)
	{
		printf("Module %d:\n",i);
		addr.start=(void *)modules[i].mod_start;
		addr.end=(void *)modules[i].mod_end;
		size_t length=addr.end-addr.start;
		physmemsetallocation(&addr);
		puts("\tOld Memory allocated");
		void *load_addr=(void *)0x200000;
		memcpy(load_addr,addr.start,length);
		puts("\tModule copied");
		addr.start=load_addr;
		addr.end=addr.start+length;
		physmemsetallocation(&addr);
		puts("\tNew Memory allocated");
		task_new(load_addr);
		puts("\tNew Task added\n");
	}
}

void physmemsetallocation(mem_allocation_t *tile)
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

mem_allocation_t *physmemgetallocation(size_t i)
{
	return phys_mem_allocation(i,0,0);
}

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
