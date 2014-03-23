#include "header.h"

int main(void)
{
	cleardisplay();
	puts("BenarydingOS Running!");
//	puts("Memorydump:");
//	memdump();
	cleardisplay();

	puts("Awaiting Input!\n");

    *(int *)0=0;

	while(1);

	exit(0);
}
