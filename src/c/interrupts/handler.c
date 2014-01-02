#include "../header.h"

void handle_interrupt(struct cpu_state* cpu)
{
	kprintf("Interrupt\n");
	while(1);
}
