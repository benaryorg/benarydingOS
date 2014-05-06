#include "header.h"

//TODO I hate global vars!
task_t *current_task=0;

/**
 * Internal interrupt handling (DO NOT USE)
 *
 * @params i the number of the entry
 * @return The pointer to the array entry (function pointer)
 */
cpu_state_t *(**interrupt_handlers(int i))(cpu_state_t *)
{
	static cpu_state_t *(*ints[256])(cpu_state_t *)={};
	return ints+i;
}

/**
 * Get the ith interrupt handler
 *
 * @param i What entry
 * @return the handler
 */
cpu_state_t *(*getinterrupthandler(int i))(cpu_state_t *)
{
	return *interrupt_handlers(i);
}

/**
 * Set the ith interrupt handler
 *
 * @param i What entry
 * @param f The Handler
 */
void setinterrupthandler(int i,cpu_state_t *(*f)(cpu_state_t *))
{
	*interrupt_handlers(i)=f;
}

/**
 * Interrupt handler for exceptions
 *
 * @praram cpu CPU state
 * @return CPU state to continue with
 */
cpu_state_t *handler_exception(cpu_state_t *cpu)
{
	int intr=cpu->intr;
	switch(intr)
	{
		case 0x00:
			puts("#DE - Division by Zero");
			break;
		case 0x01:
			puts("#DB - Debug");
			break;
		case 0x02:
			puts("#NMI - Non Maskable Interrupt");
			break;
		case 0x03:
			puts("#BP - BreakPoint");
			break;
		case 0x04:
			puts("#OF - Overflow");
			break;
		case 0x05:
			puts("#BR - Bound Range Exception");
			break;
		case 0x06:
			puts("#UD - Invalid Opcode");
			break;
		case 0x07:
			puts("#NM - Device n/a");
			break;
		case 0x08:
			kernelpanic("#DF - Double Fault");
			break;
		case 0x09:
			kernelpanic("Coprocessor Segment Overrun");
			break;
		case 0x0a:
			puts("#TS - Invalid TSS");
			break;
		case 0x0b:
			puts("#NP - Segment not Present");
			break;
		case 0x0c:
			puts("#SS - Stack Fault");
			break;
		case 0x0d:
			resetcolor();
			printf("General Protection Fault\nError Code: %u\n",(unsigned int)cpu->error);
			kernelpanic("#GP - General Protection Fault");
			break;
		case 0x0e:
			resetcolor();
			unsigned int err=cpu->error;
			int i;
			printf("Page Fault\nError Code: %u\n",err);
			for(i=0;i<5;i++)
			{
				printf("Bit %1d(%1d):\t",i,((err>>i)&1));
				switch(i)
				{
					case 0:
						puts(((err>>i)&1)?"Active Page":"Not active Page");
						break;
					case 1:
						puts(((err>>i)&1)?"Write Access":"Read Access");
						break;
					case 2:
						puts(((err>>i)&1)?"User Mode":"Kernel Mode");
						break;
					case 3:
						printf("Reserved was %d\n",((err>>i)&1));
						break;
					case 4:
						puts(((err>>i)&1)?"Code Access":"Data Access");
				}
			}
			kernelpanic("#PF - Page Fault");
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
	return cpu;
}

/**
 * Interrupt handler for hardware interrupts
 *
 * @praram cpu CPU state
 * @return CPU state to continue with
 */
cpu_state_t *handler_hardware_int(cpu_state_t *cpu)
{
	int intr=cpu->intr;
	task_t *task;
	switch(intr-0x20)
	{
		case 0x00:
//			puts("Timer");
			task=task_next(cpu);
			tss_entry_set(1,(uint32_t)(task->cpu+1));
			cpu=task->cpu;
//            printf("Switching task! id=%d\n",current_task->id);
			break;
        case 0x01:
            puts("Keyboard");
            break;
		default:
			printf("IRQ %3d\n",intr-0x20);
			break;
	}
	return cpu;
}

/**
 * Get the task by the cpu state
 *
 * @praram cpu CPU state
 * @return pointer to the task
 */
task_t *get_task_by_cpu(cpu_state_t *cpu)
{
	task_t *task=0;
	int i=0;
	do
	{
		task=task_func(i++);
	}
	while(task->cpu!=cpu&&i<TASKS_SIZE);
	return i<TASKS_SIZE?task:0;
}

/**
 * Prehandler for all Interrupts (Also resets PIC if needed)
 *
 * @param cpu CPU State
 * @return CPU state to continue with
 */
cpu_state_t *int_handler(cpu_state_t *cpu)
{
	cpu_state_t *(*f)(cpu_state_t *)=getinterrupthandler(cpu->intr);
//	task_t *task=get_task_by_cpu(cpu);
//    current_task->cpu=cpu;
	cpu_state_t *old_cpu=cpu;
	if(!f)
	{
		kernelpanic("Unhandeled Interrupt!");
	}
	else
	{
		cpu=f(cpu);
	}
    task_t *task=current_task;
    //TODO Comment
	if(old_cpu)
	{
		if(old_cpu->intr>=0x20&&old_cpu->intr<0x30)
		{
			if(old_cpu->intr<0x29)
			{
				outb(0x20,0x20);
			}
			outb(0xa0,0x20);
		}
	}
	if(old_cpu!=task->cpu)
	{
		page_activate_context(task->context);
	}
	return cpu;
}

/**
 * Get next task
 *
 * TODO fix!
 * @param cpu actual CPU state
 * @return task pointer to the next task
 */
task_t *task_next(cpu_state_t *cpu)
{
    if(current_task)
    {
        current_task->cpu=cpu;
    }
    current_task=task_schedule(current_task);
	return current_task;
}

/**
 * Creates a new CPU state, with stack and so on, cpu starts at ptr
 *
 * @param c Context for paging
 * @param ptr Pointer to the start of executable code
 * @param userspace Userspace?
 * @return CPU state
 */
cpu_state_t *cpu_new(page_context_t *c,void *ptr,char userspace)
{
	const int stackspace=16384;
	cpu_state_t cpu;
	cpu.eax=0;
	cpu.ebx=0;
	cpu.ecx=0;
	cpu.edx=0;
	cpu.esi=0;
	cpu.edi=0;
	cpu.ebp=0;
	cpu.eip=(uint32_t)ptr;
	page_map(c,((uint32_t)ptr)&~0xFFF,((uint32_t)ptr)&~0xFFF,PTE_PRESENT|PTE_WRITE|(1<<9));
	cpu.cs=0x08;
	cpu.ss=0;
	if(userspace)
	{
		cpu.cs=0x18|0x03;
		cpu.ss=0x20|0x03;
	}
	cpu.eflags=0x202;
	ptr=0;
	while(!ptr)
	{
		ptr=mallocblocks(c,stackspace/4096);
	}
	cpu.esp=(uint32_t)ptr+stackspace;
	cpu_state_t *state=(void *)(ptr+stackspace-sizeof(cpu));
	page_map(c,((uint32_t)state)&~0xFFF,((uint32_t)state)&~0xFFF,PTE_PRESENT|PTE_WRITE|(1<<9));
//	printf("%x/%x\n",&cpu,state);
    *state=cpu;
	return state;
}

/**
 * Handles the task array
 * TODO convert tasks to list
 *
 * @param i number of entry
 * @return task pointer to array element
 */
task_t *task_func(int i)
{
	static task_t tasks[TASKS_SIZE]={};
	static char setup=0;
	if(!setup)
	{
		int x;
		for(x=0;x<TASKS_SIZE;x++)
		{
			tasks[x].id=-1;
		}
		setup=1;
	}
	return tasks+i;
}

/**
 * Gets a task and returns the task to be executed next
 * TODO comment
 *
 * @param task old task
 * @return new task
 */
task_t *task_schedule(task_t *task)
{
	static int last=0;
	int i;

	if(task)
	{
		for(i=0;task_func(i)->id!=task->id&&i<TASKS_SIZE;i++);
		if(i<TASKS_SIZE)
		{
			*task_func(i)=*task;
			task=task_func(i);
		}
		else
		{
			for(i=0;task_func(i)->id>0&&i<TASKS_SIZE;i++);
			if(i<TASKS_SIZE)
			{
				*task_func(i)=*task;
				task=task_func(i);
			}
		}
		if(task->id<=0)
		{
			task->id=i+1;
			return 0;
		}
	}
	
	for(i=last+1;task_func(i)->id<=0;i++)
	{
		if(i>=TASKS_SIZE)
		{
			i=-1;
		}
	}
    last=i;
	return task_func(i);
}

/**
 * Exit current task/process
 *
 * @param ret Return value
 */
void exit(int ret)
{
	while(1)
	{
		asm("int $0x30" : : "a" (SYSCALL_TASK_EXIT), "b" (ret));
	}
}

