#include "../header.h"

void int_handler(cpu_state_t *cpu)
{
	printf("Interrupt %d\n",(int)cpu->intr);
	if(cpu->intr<0x20)
	{
		switch(cpu->intr)
		{
			case 0x0D:
				puts("General Protection Fault");
				break;
			default:
				kernelpanic("Exception");
				break;
		}
	}
	else
	{
		if(cpu->intr<0x28)
		{
			switch(cpu->intr)
			{
				case 0x20:
					puts("Timer");
					break;
			}
			outb(0x20, 0x20);
		}
		else
		{
			outb(0xa0, 0x20);
		}
	}
}
