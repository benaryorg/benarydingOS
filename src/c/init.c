#include "header.h"

void init(multiboot_info_t *mb_info)
{
	cleardisplay();
	setcolor(_color_pair(COLOR_BLACK,COLOR_LIGHT_GREEN));
	puts("benarydingOS booting");
	physmeminit(mb_info);
	puts("Physical Memory initialised");
	if(memtest(1,1))
	{
		setcolor(_color_pair(COLOR_BLACK,COLOR_LIGHT_RED));
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
