#include "header.h"

extern task_t *current_task;

void init(multiboot_info_t *mb_info)
{
	cleardisplay();
	setfgcolor(COLOR_LIGHT_GREEN);
	puts("benarydingOS booting");
	physmeminit(mb_info);
	puts("Physical Memory initialised");
	printf("Loaded %u Modules\n",(unsigned)mb_info->mbs_mods_count);
	page_context_t *c=paging_init();
	puts("Paging initialised and activated");
	pic_init();
	puts("PIC Reprogrammed");
	idt_init();
	puts("Interrupt Descriptor Table loaded");
	gdt_init();
	puts("Global Descriptor Table loaded");
	if(0)//if(memtest(128,128))
	{
		setfgcolor(COLOR_LIGHT_RED);
		memdump();
		puts("Memtest:");
		puts("Critical: Memory Overlapping!");
		puts("Please contact your local benarydingOS-supplier immediately!");
		puts("It is possible, that this is a bug!");
		kernelpanic("Memtest Failure!");
	}
	puts("Memtest OK");
	puts("Starting Main");

	task_t task;
	task.id=1;
	task.context=c;
	task.cpu=cpu_new(task.context,main,0);
	task_schedule(&task);
	resetcolor();
	asm volatile("int $0x20");
}
