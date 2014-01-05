#ifndef __HEADER_GDT__
#define __HEADER_GDT__

#define GDT_SIZE 8

#define GDT_FLAG_DATASEG 0x02
#define GDT_FLAG_CODESEG 0x0a
#define GDT_FLAG_TSS     0x09
 
#define GDT_FLAG_SEGMENT 0x10
#define GDT_FLAG_RING0   0x00
#define GDT_FLAG_RING3   0x60
#define GDT_FLAG_PRESENT 0x80

#define GDT_FLAG_4K_GRAN 0x800
#define GDT_FLAG_32_BIT  0x400

void gdt_entry_set(int,unsigned int,unsigned int,int);
uint64_t gdt_entry_get(int);
uint64_t *gdt_func(int);
void gdt_init(void);
void gdt_reload(void);

#endif
