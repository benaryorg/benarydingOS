#include "../header.h"

void int_handler(cpu_state_t *cpu)
{
	if(cpu->intr<0x20)
	{
		printf("Exception %d\n",(int)cpu->intr);
		kernelpanic("Interrupt");
	}
	if(cpu->intr==0x20)
	{
		puts("Timer");
	}
}
