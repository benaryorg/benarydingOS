#include "header.h"

int main(void)
{
	cleardisplay();
	puts("BenarydingOS Running!");
	puts("Memorydump:");
	memdump();
	cleardisplay();

	while(1)
	{
		putchar('#');
	}
	return 0;
}
