#ifndef __INTERRUPT_HANDLER_HEADER__
#define __INTERRUPT_HANDLER_HEADER__

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
    // Von Hand gesicherte Register
    uint32_t   eax;
    uint32_t   ebx;
    uint32_t   ecx;
    uint32_t   edx;
    uint32_t   esi;
    uint32_t   edi;
    uint32_t   ebp;
 
    uint32_t   intr;
    uint32_t   error;
 
    // Von der CPU gesichert
    uint32_t   eip;
    uint32_t   cs;
    uint32_t   eflags;
    uint32_t   esp;
    uint32_t   ss;
}
cpu_state_t;

void int_handler(cpu_state_t *);

#endif
