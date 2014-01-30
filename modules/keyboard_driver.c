#include "header.h"

void _start(void)
{
	while(1)
	{
		asm("int $0x30" : : "a" (SYSCALL_PUTCHAR), "b" (' '));
	}
}
