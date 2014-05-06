#include "header.h"

/**
 * Set TSS entry
 *
 * @param i what entry
 * @param data content
 */
void tss_entry_set(int i,uint32_t data)
{
	*tss_func(i)=data;
}

/**
 * Get TSS entry
 *
 * @param i What entry
 * @return Content
 */
uint32_t tss_entry_get(int i)
{
	return *tss_func(i);
}

/**
 * Backend for the TSS
 *
 * @param i entry
 * @return The pointer to the content
 */
uint32_t *tss_func(int i)
{
	static uint32_t tss[TSS_SIZE]={0,0,0x10};

	return tss+i;
}
