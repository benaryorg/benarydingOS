#include "../header.h"

void pic_init(void)
{
	//Master-PIC initialisieren
	outb(0x20, 0x11);// Initialisierungsbefehl fuer den PIC
	outb(0x21, 0x20);// Interruptnummer fuer IRQ 0
	outb(0x21, 0x04);// An IRQ 2 haengt der Slave
	outb(0x21, 0x01);// ICW 4

	// Slave-PIC initialisieren
	outb(0xa0, 0x11);// Initialisierungsbefehl fuer den PIC
	outb(0xa1, 0x28);// Interruptnummer fuer IRQ 8
	outb(0xa1, 0x02);// An IRQ 2 haengt der Slave
	outb(0xa1, 0x01);// ICW 4

	// Alle IRQs aktivieren (demaskieren)
	outb(0x20, 0x0);
	outb(0xa0, 0x0);

	activate_hardware_ints();
}

void activate_hardware_ints(void)
{
	asm volatile("sti");
}
