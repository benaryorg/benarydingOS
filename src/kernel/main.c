#include "header.h"

int main(void)
{
    puts("Main started");
	activate_hardware_ints();
	puts("Activated Hardware Interrupts");
//	cleardisplay();
	puts("benarydingOS Running!");
//	puts("Memorydump:");
//	memdump();
//	cleardisplay();

	puts("Awaiting Input!\n");

//    exit(0);

	while(1);

	exit(0);
	return 0;
}
