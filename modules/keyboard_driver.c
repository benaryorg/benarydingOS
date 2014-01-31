#include "header.h"

cpu_state_t *onkey(cpu_state_t *);

void _start(void)
{
	asm("int $0x30" : : "a" (SYSCALL_HOOK_INT), "b" (0x21), "c" (onkey));
	while(inb(0x64)&0x1)
	{
		inb(0x60);
	}

	exit(0);
}

cpu_state_t *onkey(cpu_state_t *cpu)
{
	int key=0;
	while(inb(0x64)&0x01)
	{
		key=inb(0x60);
		if(!(key&0x80))
		{
			key=inb(0x60);
			putchar(key);
		}
	}
	return cpu;
}
