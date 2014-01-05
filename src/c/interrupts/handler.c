#include "../header.h"

void int_handler(cpu_state_t *cpu)
{
	if(cpu->intr==0x20)
	{
		puts("Timer");
	}
	if(cpu->intr<0x20)
	{
		printf("Exception %d\n",(int)cpu->intr);
//		asm volatile("cli");
//		kernelpanic("Interrupt");
	}
}
