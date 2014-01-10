#include "header.h"

void init(multiboot_info_t *mb_info)
{
	cleardisplay();
	setfgcolor(COLOR_LIGHT_GREEN);
	puts("benarydingOS booting");
	pic_init();
	puts("PIC Reprogrammed");
	idt_init();
	puts("Interrupt Descriptor Table loaded");
	gdt_init();
	puts("Global Descriptor Table loaded");
	physmeminit(mb_info);
	puts("Physical Memory initialised");
	printf("Loaded %d Modules\n",(int)mb_info->mbs_mods_count);
	if(memtest(1024,1024))
	{
		setfgcolor(COLOR_LIGHT_RED);
		memdump();
		puts("Memtest:");
		puts("Critical: Memory Overlapping!");
		puts("Please contact your local benarydingOS-supplier immediately!");
		puts("It is possible, that this is a bug!");
		kernelpanic("Memtest Failure!");
		return;
	}
	puts("Memtest OK");
	activate_hardware_ints();
	puts("Activated Hardware Interrupts");
	puts("Starting Main\n");
	resetcolor();
	main();
}
