#ifndef __GDT_HEADER__
#define __GDT_HEADER__

#define GDT_ENTRIES 65500

#define GDT_FLAG_DATASEG 0x02
#define GDT_FLAG_CODESEG 0x0a
#define GDT_FLAG_TSS     0x09
 
#define GDT_FLAG_SEGMENT 0x10
#define GDT_FLAG_RING0   0x00
#define GDT_FLAG_RING3   0x60
#define GDT_FLAG_PRESENT 0x80
 
#define GDT_FLAG_4K_GRAN 0x800
#define GDT_FLAG_32_BIT  0x400

static uint64_t gdt[GDT_ENTRIES];

void init_gdt(void);
void set_gdt_entry(int i,unsigned int base,unsigned int limit,int flags);
void load_gdt(void);

#endif
