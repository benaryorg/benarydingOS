#include "header.h"

int main(void)
{
	cleardisplay();
	puts("BenarydingOS Running!");
	puts("Memorydump:");
	memdump();
//	cleardisplay();
	printf("%d",4/0);
//	asm volatile("int $0x00");
	return 0;
}
