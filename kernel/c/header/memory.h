#ifndef __MEMORY_HEADER__
#define __MEMORY_HEADER__

#define MEM_FREE 1
#define MEM_BLOCK_SIZE 0x1000
#define MEM_STACK_SIZE (1<<16)

extern const void _KERNEL_START;
extern const void _KERNEL_END;

typedef struct
{
	void *start;
	void *end;
}
mem_allocation_t;

void *malloc(unsigned int);
void free(void *);

void physmeminit(multiboot_info_t *);
mem_allocation_t *physmemgetallocation(size_t);
void physmemsetallocation(mem_allocation_t *);
void physmemrmalloc(void *);
mem_allocation_t *phys_mem_allocation(size_t,mem_allocation_t *,char);

int memtest(const int arrs,const int bytes);
void memdump(void);

void *memcpy(void *,const void *,unsigned int);
void *memset(void *,int,unsigned int);

#endif
