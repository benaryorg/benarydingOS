#include "header.h"

void foo(void)
{
	while(1)
	{
		//putchar('#');
		//asm volatile("cli;hlt");
	}
}

int main(void)
{
	cleardisplay();
	puts("BenarydingOS Running!");
	puts("Memorydump:");
	memdump();
	cleardisplay();

	//task_new(foo);

	while(1);
	return 0;
}
