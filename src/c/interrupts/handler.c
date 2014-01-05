#include "../header.h"

void int_handler(cpu_state_t *cpu)
{
	printf("Interrupt %d\n",(int)cpu->intr);
	if(cpu->intr<0x20)
	{
		kernelpanic("Exception");
	}
	else
	{
		if(cpu->intr>0x27)
		{
			switch(cpu->intr)
			{
				case 0x20:
					puts("Timer");
					break;
			}
			outb(0xa0, 0x20);
		}
		outb(0x20, 0x20);
	}
}
