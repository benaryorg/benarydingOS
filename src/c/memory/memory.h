#ifndef __MEMORY_HEADER__
#define __MEMORY_HEADER__

#define MEM_FREE 1
#define MEM_BLOCK_SIZE 0x1000
#define MEM_STACK_SIZE (1<<15)

extern const void _KERNEL_START;
extern const void _KERNEL_END;

typedef struct
{
	uint16_t size;
	uintptr_t BaseAddr;
	uint32_t Length;
	uint16_t Type;
}
multiboot_mmap_t;

typedef struct
{
	uint16_t mbs_flags;
	uint16_t mbs_mem_lower;
	uint16_t mbs_mem_upper;
	uint16_t mbs_bootdevice;
	uint16_t mbs_cmdline;
	uint16_t mbs_mods_count;
	uint16_t mbs_mods_addr;
	uint64_t mbs_syms;
	uint16_t mbs_mmap_length;
	multiboot_mmap_t *mbs_mmap_addr;
	uint16_t mbs_drives_length;
	uint16_t mbs_drives_addr;
	uint16_t mbs_config_table;
	uint16_t mbs_boot_loader_name;
	uint16_t mbs_apm_table;
	uint16_t mbs_vbe_control_info;
	uint16_t mbs_vbe_mode_info;
	uint8_t mbs_vbe_mode;
	uint8_t mbs_vbe_interface_seg;
	uint8_t mbs_vbe_interface_off;
	uint8_t mbs_vbe_interface_len;
}
multiboot_info_t;

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

void *memcpy(void *,const void *,size_t);
void *memset(void *,int,size_t);

#endif
