#include "header.h"

enum spkr_code {
    SPKR_BELL = 0x00,
    SPKR_TONE = 0x01,
};

int pcspeaker_event(unsigned int code, int value);
void pcspeaker_off();
void pcspeaker_beep();

void _start(void)
{
    pcspeaker_event(SPKR_TONE, 1000);
    exit(0);
}

int pcspeaker_event(unsigned int code, int value) {
	unsigned int tick_rate = 1193182; /* PIT tick rate = 1.193182 MHz */
	
	unsigned int count = 0;
	
	switch (code) {
		case SPKR_BELL: { 
			if (value) {
				value = 1000;
			}
			break;
		}
		case SPKR_TONE: {
			break;
		}
		default: {
			return -1;
		}
	}
	
	if (value > 20 && value < 32767) {
		count = tick_rate / value;
	}
	
	if (count) {
		/* setting command for counter 2 */
		outb(0xb6, 0x43);
		/* setting the PIT to the desired Hz */
		outb(0x42, count & 0xff);
		outb(0x42, (count >> 8) & 0xff);
		/* enable counter 2 */
		outb(0x61, inb(0x61) | 3);
	} else {
		/* disable counter 2 */
		outb(0x61, inb(0x61) & 0xfc);
	}
	
	return 0;
}

void pcspeaker_off() {
	pcspeaker_event(SPKR_BELL, 0);
}

void pcspeaker_beep() {
	pcspeaker_event(SPKR_BELL, 1);
	int i = 0;
	/* TODO: we need a proper wait function */
	for (; i < 10000; i++)
		;
	pcspeaker_off();
}