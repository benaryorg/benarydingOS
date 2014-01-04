#include "header.h"

void init(multiboot_info_t *mb_info)
{
	cleardisplay();
	puts("Started");
	physmeminit(mb_info);
	puts("Physical Memory initialised");

	puts("Starting Main\n");
	main();
}
