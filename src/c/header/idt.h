#ifndef __HEADER_IDT__
#define __HEADER_IDT__

#define IDT_SIZE 256

typedef struct
{
	uint16_t lsb_handler;
	uint16_t selector;
	uint8_t reserved;
	uint8_t access;
	uint16_t msb_handler;
}
int_desc_t;

int_desc_t idt_entry_get(int);
int_desc_t *idt_func(int);
void idt_init(void);
void idt_entry_set(int,uint16_t,void *,int,int);

#endif
