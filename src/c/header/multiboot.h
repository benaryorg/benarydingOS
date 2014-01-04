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

#endif
