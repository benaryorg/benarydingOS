#include "header.h"

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
