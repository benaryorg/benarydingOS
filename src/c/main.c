#include "header.h"

int init(multiboot_info_t *mb_info)
{
	physmeminit(mb_info);
	cleardisplay();
	
	printf("Hello, world!\n");
	
	return 0;
}
