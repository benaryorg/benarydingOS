#ifndef __MEMORY_HEADER__
#define __MEMORY_HEADER__

#define MEM_FREE 1
#define MEM_BLOCK_SIZE 0x1000
#define MEM_STACK_SIZE (1<<20)

extern const void _KERNEL_START;
extern const void _KERNEL_END;

typedef struct
{
	void *start;
	void *end;
}
mem_allocated_t;

void *malloc(size_t);
void free(void *);

void physmeminit(multiboot_info_t *);
mem_allocated_t *physmemgetallocation(size_t);
void physmemsetallocation(mem_allocated_t *);
void physmemrmalloc(void *);
mem_allocated_t *phys_mem_allocation(size_t,mem_allocated_t *,char);

int memtest(const int arrs,const int bytes);
void memdump(void);

void *memcpy(void *,const void *,size_t);
void *memset(void *,int,size_t);

#endif
