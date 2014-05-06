#include "header.h"

//Current task //TODO fix this
extern task_t *current_task;

/**
 * Function for handling the syscall handlers
 *
 * @param i The function (0-255)
 * @return A pointer to the function pointer in the array
 */
cpu_state_t *(**syscall_handlers(int i))(cpu_state_t *)
{
	static cpu_state_t *(*syscalls[256])(cpu_state_t *)={};
	return syscalls+i;
}

/**
 * Return the function pointer to the ith syscall handler function
 *
 * @param i The ith function
 * @return The function pointer
 */
cpu_state_t *(*getsyscallhandler(int i))(cpu_state_t *)
{
	return *syscall_handlers(i);
}

/**
 * Sets the syscallhandler for the syscall i
 *
 * @param i What syscall
 * @param f The function pointer
 */
void setsyscallhandler(int i,cpu_state_t *(*f)(cpu_state_t *))
{
	if(i>0xFF)
	{
		*syscall_handlers(i)=f;
	}
}

/**
 * The handler function for syscalls (interrupt 0x30)
 *
 * @param cpu The cpu state
 * @return The cpu state after the syscall
 */
cpu_state_t *handler_syscall(cpu_state_t *cpu)
{
	task_t *task;
	cpu_state_t *(*f)(cpu_state_t *)=getsyscallhandler(cpu->eax);
    //If an other syscall handler is set, call this one
	if(f)
	{
		return f(cpu);
	}
    //Standard syscalls
	switch(cpu->eax)
	{
        //Putchar is handeled by the system
		case SYSCALL_PUTCHAR:
			putchar(cpu->ebx);
			break;
        //Clear the display
		case SYSCALL_CLEAR:
			cleardisplay();
			break;
        //Hook an interrupt
		case SYSCALL_HOOK_INT:
			setinterrupthandler(cpu->ebx,(void *)cpu->ecx);
			break;
        //Hook a syscall
		case SYSCALL_HOOK_SYSCALL:
			setsyscallhandler(cpu->ebx,(void *)cpu->ecx);
			break;
        //Inb
		case SYSCALL_INB:
			*(int *)(cpu->ecx)=inb(cpu->ebx);
			break;
        //Outb
		case SYSCALL_OUTB:
			outb(cpu->ebx,cpu->ecx);
			break;
        //Exit the Task
		case SYSCALL_TASK_EXIT:
			task=current_task;
            //TODO free the task
//			freetask(task);
			task->id=-1;
        //Quickly jump to the next task
		case SYSCALL_TASK_NEXT:
			asm volatile("int $0x20");
			break;
//		  free(task->context);
//			return task_next()->cpu;
        //Get the current CPU state
		case SYSCALL_GET_CPU:
			*(uint32_t *)cpu->ebx=(uint32_t)cpu;
			break;
        //TODO Reboot Syscall
		case SYSCALL_REBOOT:
			break;
        //TODO Find a better way to handle that
		default:
			kernelpanic("Unknown Syscall");
			break;
	}
	return cpu;
}

