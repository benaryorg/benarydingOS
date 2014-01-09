#include "header.h"

void foo(void)
{
	int i;
	while(1)
	{
		i=5/0;
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

	while(1);
	return 0;
}
