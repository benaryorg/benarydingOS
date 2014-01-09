#ifndef __MULTIBOOT_HEADER__
#define __MULTIBOOT_HEADER__

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
	uint32_t mod_start;
	uint32_t mod_end;
	uint32_t string;
	uint32_t reserved;
}
multiboot_module_t;

typedef struct
{
	uint32_t mbs_flags;
	uint32_t mbs_mem_lower;
	uint32_t mbs_mem_upper;
	uint32_t mbs_bootdevice;
	uint32_t mbs_cmdline;
	uint32_t mbs_mods_count;
	multiboot_module_t *mbs_mods_addr;
	uint64_t mbs_syms1;
	uint64_t mbs_syms2;
	uint32_t mbs_mmap_length;
	multiboot_mmap_t *mbs_mmap_addr;
	uint32_t mbs_drives_length;
	uint32_t mbs_drives_addr;
	uint32_t mbs_config_table;
	uint32_t mbs_boot_loader_name;
	uint32_t mbs_apm_table;
	uint32_t mbs_vbe_control_info;
	uint32_t mbs_vbe_mode_info;
	uint16_t mbs_vbe_mode;
	uint16_t mbs_vbe_interface_seg;
	uint16_t mbs_vbe_interface_off;
	uint16_t mbs_vbe_interface_len;
}
multiboot_info_t;

#endif
