#include "../header.h"

cpu_state_t *get_new_cpu(void)
{
	cpu_state_t *cpu=malloc(sizeof(cpu_state_t));
		return cpu;
}

cpu_state_t *int_handler(cpu_state_t *cpu)
{
	char key;
	if(!cpu)
	{
		return 0;
	}
	unsigned int intr=cpu->intr;
	if(intr<0x20)
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
				puts("Invalid TSS");
				break;
			case 0x0b:
				puts("Segment not Present");
				break;
			case 0x0c:
				puts("Stack Fault");
				break;
			case 0x0d:
				resetcolor();
				printf("General Protection Fault\nError Code: %u\n",(unsigned int)cpu->error);
				kernelpanic("#GP");
				break;
			case 0x0e:
				puts("Page Fault");
				break;
			case 0x10:
				puts("#MF - x87 Floating Point");
				break;
			case 0x11:
				kernelpanic("#AC - Alignment Check");
				break;
			case 0x12:
				puts("#MC - Machine Check");
				break;
			case 0x13:
				puts("#XF - SIMD Floating Point");
				break;
			case 0x0f:
			case 0x14:
			case 0x15:
			case 0x16:
			case 0x17:
			case 0x18:
			case 0x19:
			case 0x1a:
			case 0x1b:
			case 0x1c:
			case 0x1d:
			case 0x1f:
				kernelpanic("Reserved Exception");
				break;
			case 0x1e:
				kernelpanic("#SX - Security-sensitive event in Host");
			default:
				printf("Exception %d\n",intr);
				kernelpanic("It is impossible to get this Error!\nIf you have this Error, please kill yourself, you have no life and no friends!");
				break;
		}
		//kernelpanic("Exception");
	}
	else
	{
		if(intr<0x30)
		{
			switch(intr-0x20)
			{
				case 0x00:
//					puts("Timer");
					cpu=task_next(cpu);
					tss_entry_set(1,(uint32_t)(cpu+1));
					break;
				case 0x01://Typing (only for testing!)
					while(inb(0x64)&0x01)
						key=inb(0x60);
						if(!(key&0x80))
							printf("Taste %d\n",inb(0x60));
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
			switch(intr-0x30)
			{
				case 0x00:
					syscall_handle(cpu);
					break;
				default:
					kernelpanic("Something happened");
					break;
			}
		}
	}
	return cpu;
}

void syscall_handle(cpu_state_t *cpu)
{
	switch(cpu->eax)
	{
		case 0x00:
			putchar(cpu->ebx);
			break;
		default:
			kernelpanic("Unknown Syscall");
			break;
	}
}

cpu_state_t *task_next(cpu_state_t *task)
{
	return task_schedule(task,0);
}

void task_new(void *ptr,char userspace)
{
	const int stackspace=4096;
	cpu_state_t cpu;
	cpu.eax=0;
	cpu.ebx=0;
	cpu.ecx=0;
	cpu.edx=0;
	cpu.esi=0;
	cpu.edi=0;
	cpu.ebp=0;
	cpu.eip=(uint32_t)ptr;
	cpu.cs=0x08;
	if(userspace)
	{
		cpu.cs=0x18|0x03;
		cpu.ss=0x20|0x03;
	}
	cpu.eflags=0x202;
	ptr=0;
	while(!ptr)
	{
		ptr=malloc(stackspace);
	}
	cpu.esp=(uint32_t)ptr+stackspace;
	cpu_state_t *state=(void *)(ptr+stackspace-sizeof(cpu));
	*state=cpu;
	task_schedule(state,1);
}

cpu_state_t *task_schedule(cpu_state_t *task,char add)
{
	static task_t tasks[TASKS_SIZE]={};

	int i;

	for(i=0;tasks[i].cpu&&i<TASKS_SIZE;i++);
	if(i<TASKS_SIZE)
	{
		tasks[i].cpu=task;
		tasks[i].ticks=3;
		tasks[i].tick=4;
	}

	if(add)
	{
		return 0;
	}
	
	task=0;

	do
	{
		for(i=0;i<TASKS_SIZE;i++)
		{
			if(tasks[i].ticks>tasks[i].tick)
			{
				tasks[i].tick++;
				task=tasks[i].cpu;
				tasks[i].cpu=0;
				break;
			}
		}
		if(!task)
		{
			for(i=0;i<TASKS_SIZE;i++)
			{
				tasks[i].tick=0;
			}
		}
	} while(!task);
	return task;
}
