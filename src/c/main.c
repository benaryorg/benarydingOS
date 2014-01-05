#include "header.h"

int main(void)
{
	cleardisplay();
	activate_hardware_ints();
	puts("BenarydingOS Running!");
	puts("Memorydump:");
	memdump();
	cleardisplay();
	return 0;
}
