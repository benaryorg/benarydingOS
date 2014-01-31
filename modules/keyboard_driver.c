#include "header.h"

cpu_state_t *onkey(cpu_state_t *);
int inb(int);
int putchar(int);
void exit(int);

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

void exit(int ret)
{
	while(1)
	{
		asm("int $0x30" : : "a" (SYSCALL_TASK_EXIT), "b" (ret));
	}
}

int putchar(int ch)
{
	asm("int $0x30" : : "a" (SYSCALL_PUTCHAR), "b" (ch));
	return ch;
}

int inb(int port)
{
	int res;
	asm("int $0x30" : : "a" (SYSCALL_INB), "b" (port), "c" (&res));
	return res;
}
