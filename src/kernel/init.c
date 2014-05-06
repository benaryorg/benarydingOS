#include "header.h"

//The current task variable
extern task_t *current_task;

/**
 * Function started by the assembler start.S
 *
 * @param mb_info The multiboot structure
 */
void init(multiboot_info_t *mb_info)
{
    //First clear the display and remove the BIOS Message
	cleardisplay();
    //Set the foregroundcolor to light green for system messages
	setfgcolor(COLOR_LIGHT_GREEN);
	puts("benarydingOS booting");
    //Initialise the physical memory management
	physmeminit(mb_info);
	puts("Physical Memory initialised");
	printf("Loaded %u Modules\n",(unsigned)mb_info->mbs_mods_count);
    //Initialise paging and save the created context
	page_context_t *c=paging_init();
	puts("Paging initialised and activated");
    //Reprogram the programmable interrupt controller
	pic_init();
	puts("PIC Reprogrammed");
    //Initialise the interrupt descriptor table
	idt_init();
	puts("Interrupt Descriptor Table loaded");
    //Initialise the global descriptor table
	gdt_init();
	puts("Global Descriptor Table loaded");
    //Run a memtest //TODO fix memtest
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

    //Create the first task
	task_t task;
    task.id=0;
	task.context=c;
    //Create a new cpu state
	task.cpu=cpu_new(task.context,main,0);
    //Add the new task to the scheduler
	task_schedule(&task);
    //Activate the interrupts
	activate_hardware_ints();
	puts("Activated Hardware Interrupts");
    //Reset the color for the main
	resetcolor();
    //schedule the next task
	asm volatile("int $0x20");
}
