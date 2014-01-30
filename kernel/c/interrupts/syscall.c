#include "header.h"

cpu_state_t *handler_syscall(cpu_state_t *cpu)
{
	switch(cpu->eax)
	{
		case SYSCALL_PUTCHAR:
			putchar(cpu->ebx);
			break;
		case SYSCALL_CLEAR:
			cleardisplay();
			break;
		case SYSCALL_REBOOT:
			break;
		case SYSCALL_TASK_NEXT:
			asm volatile("int $0x20");
			break;
		case SYSCALL_HOOK_INT:
			setinterrupthandler(cpu->ebx,(void *)cpu->ecx);
			break;
		case SYSCALL_INB:
			*(int *)(cpu->ecx)=inb(cpu->ebx);
			break;
		default:
			kernelpanic("Unknown Syscall");
			break;
	}
	return cpu;
}

