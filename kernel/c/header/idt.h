#ifndef __HEADER_IDT__
#define __HEADER_IDT__

#define IDT_SIZE 256

#define IDT_TASK_GATE 0x9
#define IDT_INTERRUPT_GATE 0xe
#define IDT_TRAP_GATE 0xf

extern const void intr_stub_0(void);
extern const void intr_stub_1(void);
extern const void intr_stub_2(void);
extern const void intr_stub_3(void);
extern const void intr_stub_4(void);
extern const void intr_stub_5(void);
extern const void intr_stub_6(void);
extern const void intr_stub_7(void);
extern const void intr_stub_8(void);
extern const void intr_stub_9(void);
extern const void intr_stub_10(void);
extern const void intr_stub_11(void);
extern const void intr_stub_12(void);
extern const void intr_stub_13(void);
extern const void intr_stub_14(void);
extern const void intr_stub_15(void);
extern const void intr_stub_16(void);
extern const void intr_stub_17(void);
extern const void intr_stub_18(void);

extern const void intr_stub_32(void);
extern const void intr_stub_33(void);
extern const void intr_stub_34(void);
extern const void intr_stub_35(void);
extern const void intr_stub_36(void);
extern const void intr_stub_37(void);
extern const void intr_stub_38(void);
extern const void intr_stub_39(void);
extern const void intr_stub_40(void);
extern const void intr_stub_41(void);
extern const void intr_stub_42(void);
extern const void intr_stub_43(void);
extern const void intr_stub_44(void);
extern const void intr_stub_45(void);
extern const void intr_stub_46(void);
extern const void intr_stub_47(void);

extern const void intr_stub_48(void);

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
