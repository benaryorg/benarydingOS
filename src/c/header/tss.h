#ifndef __TSS_HEADER__
#define __TSS_HEADER__

#define TSS_SIZE 128

void tss_init(void);
void tss_entry_set(int,uint32_t);
uint32_t tss_entry_get(int);
uint32_t *tss_func(int);

#endif
