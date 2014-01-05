#include "header.h"

void init(multiboot_info_t *mb_info)
{
	cleardisplay();
	setcolor(_color_pair(COLOR_BLACK,COLOR_LIGHT_GREEN));
	puts("benarydingOS booting");
	gdt_init();
	puts("Global Descriptor Table loaded");
	idt_init();
	puts("Interrupt Descriptor Table loaded");
	physmeminit(mb_info);
	puts("Physical Memory initialised");
	if(memtest(128,128))
	{
		kernelpanic("Memtest Failure!");
		setcolor(_color_pair(COLOR_BLACK,COLOR_LIGHT_RED));
		memdump();
		puts("Memtest:");
		puts("Critical: Memory Overlapping!");
		puts("Please contact your local benarydingOS-supplier immediately!");
		puts("It is possible, that this is a bug!");
		return;
	}
	puts("Starting Main\n");
	resetcolor();
	main();
}
