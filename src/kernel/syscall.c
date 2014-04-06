#include "header.h"

extern task_t *current_task;

cpu_state_t *(**syscall_handlers(int i))(cpu_state_t *)
{
	static cpu_state_t *(*syscalls[256])(cpu_state_t *)={};
	return syscalls+i;
}

cpu_state_t *(*getsyscallhandler(int i))(cpu_state_t *)
{
	return *syscall_handlers(i);
}

void setsyscallhandler(int i,cpu_state_t *(*f)(cpu_state_t *))
{
	if(i>0xFF)
	{
		*syscall_handlers(i)=f;
	}
}

cpu_state_t *handler_syscall(cpu_state_t *cpu)
{
	task_t *task;
	cpu_state_t *(*f)(cpu_state_t *)=getsyscallhandler(cpu->eax);
	if(f)
	{
		return f(cpu);
	}
	switch(cpu->eax)
	{
		case SYSCALL_PUTCHAR:
			putchar(cpu->ebx);
			break;
		case SYSCALL_CLEAR:
			cleardisplay();
			break;
		case SYSCALL_HOOK_INT:
			setinterrupthandler(cpu->ebx,(void *)cpu->ecx);
			break;
		case SYSCALL_HOOK_SYSCALL:
			setsyscallhandler(cpu->ebx,(void *)cpu->ecx);
			break;
		case SYSCALL_INB:
			*(int *)(cpu->ecx)=inb(cpu->ebx);
			break;
		case SYSCALL_OUTB:
			outb(cpu->ebx,cpu->ecx);
			break;
		case SYSCALL_TASK_EXIT:
			task=current_task;
//			freetask(task);
			task->id=-1;
		case SYSCALL_TASK_NEXT:
			asm volatile("int $0x20");
			break;
//		  free(task->context);
//			return task_next()->cpu;
		case SYSCALL_GET_CPU:
			*(uint32_t *)cpu->ebx=(uint32_t)cpu;
			break;
		case SYSCALL_REBOOT:
			break;
		default:
			kernelpanic("Unknown Syscall");
			break;
	}
	return cpu;
}

