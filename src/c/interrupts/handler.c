#include "../header.h"

void interrupt_handler(struct cpu_state* cpu)
{
	kprintf("Interrupt\n");
	while(1);
}
