#include "header.h"

int main(void)
{
	load_gdt();
	load_idt();
	cleardisplay();
	asm volatile("int $0x0");
	while(1);
	return 0;
}
