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
		asm volatile("int $0x20");
	}
	return 0;
}
