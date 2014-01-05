#include "../header.h"

void idt_entry_set(int intr,uint16_t selector,void *handler,int dpl,int type)
{
	int_desc_t entry;
	entry.lsb_handler=((uint32_t)handler)&0xFFFF;
	entry.msb_handler=(((uint32_t) handler)>>16)&0xFFFF;
	entry.access=0x80|((dpl&3)<<5)|type;
	entry.selector=selector;
	entry.reserved=0;
	*idt_func(intr)=entry;
}

int_desc_t idt_entry_get(int i)
{
	return *idt_func(i);
}

int_desc_t *idt_func(int i)
{
	static int_desc_t idt[IDT_SIZE]={};
	
	return idt+i;
}

void idt_init(void)
{
	idt_entry_set(0,0x08,int_handler,0,0x07);

	struct
	{
		uint16_t limit;
		void *ptr;
	}
	__attribute__((packed)) idtptr=
	{
		.limit=IDT_SIZE*8-1,
		.ptr=idt_func(0),
	};

	asm volatile("lidt %0" : : "m" (idtptr));
	register_reload();
}
