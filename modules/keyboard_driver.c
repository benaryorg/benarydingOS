#include "header.h"

cpu_state_t *onkey(cpu_state_t *);

void _start(void)
{
	asm("int $0x30" : : "a" (SYSCALL_HOOK_INT), "b" (0x21), "c" (onkey));
	while(1);
}

cpu_state_t *onkey(cpu_state_t *cpu)
{
	char key=0;
//	while(inb(0x64)&0x01)
	{
//		key=inb(0x60);
//		asm("int $0x30" : : "a" (SYSCALL_PUTCHAR), "b" ('#'));
		if(!(key&0x80))
		{
			asm("int $0x30" : : "a" (SYSCALL_PUTCHAR), "b" ('#'));
//			printf("Taste %d\n",inb(0x60));
//			break;
		}
	}
	return cpu;
}
