#include "header.h"

int main(void)
{
	cleardisplay();
	puts("BenarydingOS Running!");
	puts("Memorydump:");
	memdump();
	cleardisplay();

	puts("Awaiting Input!\n");

	while(1);

  	exit(0);
	return 0;
}
