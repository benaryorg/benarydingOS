#ifndef __HEADER_IDT__
#define __HEADER_IDT__

#define IDT_SIZE 256

uint64_t idt_entry_get(int);
uint64_t *idt_func(int);
//void idt_entry_set(int,unsigned int,unsigned int,int);
//void idt_init(void);
//void idt_reload(void);

#endif
