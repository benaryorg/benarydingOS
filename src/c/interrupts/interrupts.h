#ifndef __IDT_HEADER__
#define __IDT_HEADER__

#define IDT_ENTRIES 65500

#define IDT_FLAG_DATASEG 0x02
#define IDT_FLAG_CODESEG 0x0a
#define IDT_FLAG_TSS     0x09
 
#define IDT_FLAG_SEGMENT 0x10
#define IDT_FLAG_RING0   0x00
#define IDT_FLAG_RING3   0x60
#define IDT_FLAG_PRESENT 0x80
 
#define IDT_FLAG_4K_GRAN 0x800
#define IDT_FLAG_32_BIT  0x400

static uint64_t idt[IDT_ENTRIES];

struct cpu_state
{
	uint32_t   eax;
	uint32_t   ebx;
	uint32_t   ecx;
	uint32_t   edx;
	uint32_t   esi;
	uint32_t   edi;
	uint32_t   ebp;

	uint32_t   intr;
	uint32_t   error;

	uint32_t   eip;
	uint32_t   cs;
	uint32_t   eflags;
	uint32_t   esp;
	uint32_t   ss;
};

void init_idt(void);
void set_idt_entry(int i,unsigned int base,unsigned int limit,int flags);
void load_idt(void);
void handle_interrupt(struct cpu_state* cpu);

#endif
