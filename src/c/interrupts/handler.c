#include "../header.h"

cpu_state_t *get_new_cpu(void)
{
	cpu_state_t *cpu=malloc(sizeof(cpu_state_t));
	cpu->eax=0;
	cpu->ebx=0;
	cpu->ecx=0;
	cpu->edx=0;
	cpu->esi=0;
	cpu->edi=0;
	cpu->ebp=0;
	cpu->eip=0;
	cpu->cs=0x08;
	cpu->eflags=0x202;
	return cpu;
}

cpu_state_t *int_handler(cpu_state_t *cpu)
{
	if(!cpu)
	{
		return 0;
	}
	unsigned int intr=cpu->intr;
	if(intr<0x10)
	{
		switch(intr)
		{
			case 0x00:
				puts("Division by Zero");
				break;
			case 0x01:
				puts("Debug Exception");
				break;
			case 0x02:
				puts("Non Maskable Interrupt Exception");
				break;
			case 0x03:
				puts("BreakPoint");
				break;
			case 0x04:
				puts("Overflow");
				break;
			case 0x05:
				puts("Bound Range Exception");
				break;
			case 0x06:
				puts("Invalid Opcode");
				break;
			case 0x07:
				puts("Device n/a");
				break;
			case 0x08:
				kernelpanic("Double Fault");
				break;
			case 0x09:
				kernelpanic("Coprocessor Segment Overrun");
				break;
			case 0x0a:
				puts("Invalit TSS");
				break;
			case 0x0b:
				puts("Segment not Present");
				break;
			case 0x0c:
				puts("Stack Fault");
				break;
			case 0x0d:
				printf("General Protection Fault\nError Code: %u\n",(unsigned int)cpu->error);
				break;
			case 0x0e:
				puts("Page Fault");
				break;
			case 0x0f:
				kernelpanic("Reserved Exception");
				break;
			default:
				kernelpanic("It is impossible to get this Error!\nIf you have this Error, please kill yourself, you have no life and no friends!");
				break;
		}
		kernelpanic("Exception");
	}
	else
	{
		if(intr<0x20)
		{
			kernelpanic("Exception>0x0f");
		}
		else
		{
			if(intr<0x30)
			{
				switch(intr-0x20)
				{
					case 0x00:
						puts("Timer");
						break;
					default:
						printf("IRQ %3d\n",intr-0x20);
						break;
				}
				if(intr<0x29)
				{
					outb(0x20,0x20);
				}
				outb(0xa0,0x20);
			}
			else
			{
				kernelpanic("Something happened!");
			}
		}
	}
	return cpu;
}
