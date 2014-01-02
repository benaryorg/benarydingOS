#include "../header.h"

void interrupt_handler(void)
{
	kprintf("Interrupt\n");
	while(1);
}
