#include "header.h"

int main(void)
{
	cleardisplay();
	puts("BenarydingOS Running!");
	puts("Memorydump:");
	memdump();
//	cleardisplay();
	asm volatile("int $0x00");
	return 0;
}
