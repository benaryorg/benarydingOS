#include "../header.h"

void idt_entry_set(int intr,uint16_t selector,void *handler,int dpl,int type)
{
	int_desc_t entry;
	entry.lsb_handler=((uint32_t)handler)&0xFFFF;
	entry.msb_handler=(((uint32_t)handler)>>16)&0xFFFF;
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
	idt_entry_set(0,0x08,intr_stub_0 ,0,IDT_TRAP_GATE);
	idt_entry_set(1,0x08,intr_stub_1 ,0,IDT_TRAP_GATE);
	idt_entry_set(2,0x08,intr_stub_2 ,0,IDT_TRAP_GATE);
	idt_entry_set(3,0x08,intr_stub_3 ,0,IDT_TRAP_GATE);
	idt_entry_set(4,0x08,intr_stub_4 ,0,IDT_TRAP_GATE);
	idt_entry_set(5,0x08,intr_stub_5 ,0,IDT_TRAP_GATE);
	idt_entry_set(6,0x08,intr_stub_6 ,0,IDT_TRAP_GATE);
	idt_entry_set(7,0x08,intr_stub_7 ,0,IDT_TRAP_GATE);
	idt_entry_set(8,0x08,intr_stub_8 ,0,IDT_TRAP_GATE);
	idt_entry_set(9,0x08,intr_stub_9 ,0,IDT_TRAP_GATE);
	idt_entry_set(10,0x08,intr_stub_10,0,IDT_TRAP_GATE);
	idt_entry_set(11,0x08,intr_stub_11,0,IDT_TRAP_GATE);
	idt_entry_set(12,0x08,intr_stub_12,0,IDT_TRAP_GATE);
	idt_entry_set(13,0x08,intr_stub_13,0,IDT_TRAP_GATE);
	idt_entry_set(14,0x08,intr_stub_14,0,IDT_INTERRUPT_GATE);
	idt_entry_set(15,0x08,intr_stub_15,0,IDT_TRAP_GATE);
	idt_entry_set(16,0x08,intr_stub_16,0,IDT_TRAP_GATE);
	idt_entry_set(17,0x08,intr_stub_17,0,IDT_TRAP_GATE);
	idt_entry_set(18,0x08,intr_stub_18,0,IDT_TRAP_GATE);

	idt_entry_set(32,0x08,intr_stub_32,0,IDT_INTERRUPT_GATE);
	idt_entry_set(33,0x08,intr_stub_33,0,IDT_TRAP_GATE);
	idt_entry_set(34,0x08,intr_stub_34,0,IDT_TRAP_GATE);
	idt_entry_set(35,0x08,intr_stub_35,0,IDT_TRAP_GATE);
	idt_entry_set(36,0x08,intr_stub_36,0,IDT_TRAP_GATE);
	idt_entry_set(37,0x08,intr_stub_37,0,IDT_TRAP_GATE);
	idt_entry_set(38,0x08,intr_stub_38,0,IDT_TRAP_GATE);
	idt_entry_set(39,0x08,intr_stub_39,0,IDT_TRAP_GATE);
	idt_entry_set(40,0x08,intr_stub_40,0,IDT_TRAP_GATE);
	idt_entry_set(41,0x08,intr_stub_41,0,IDT_TRAP_GATE);
	idt_entry_set(42,0x08,intr_stub_42,0,IDT_TRAP_GATE);
	idt_entry_set(43,0x08,intr_stub_43,0,IDT_TRAP_GATE);
	idt_entry_set(44,0x08,intr_stub_44,0,IDT_TRAP_GATE);
	idt_entry_set(45,0x08,intr_stub_45,0,IDT_TRAP_GATE);
	idt_entry_set(46,0x08,intr_stub_46,0,IDT_TRAP_GATE);
	idt_entry_set(47,0x08,intr_stub_47,0,IDT_TRAP_GATE);

	idt_entry_set(48,0x08,intr_stub_48,0,IDT_TRAP_GATE);

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
