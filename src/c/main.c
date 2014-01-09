#include "header.h"

void foo(void)
{
	while(1)
	{
		putchar('#');
	}
}

int main(void)
{
	cleardisplay();
	puts("BenarydingOS Running!");
	puts("Memorydump:");
	memdump();
	cleardisplay();

	task_new(foo);

	while(1)
	{
		putchar(' ');
	}
	return 0;
}
