#ifndef __PCSPEAKER_H__
#define __PCSPEAKER_H__

#include "header.h"

enum spkr_code {
	SPKR_BELL = 0x00,
	SPKR_TONE = 0x01,
};

int pcspeaker_event(unsigned int code, int value);
void pcspeaker_off();
void pcspeaker_beep();

#endif /* __PCSPEAKER_H__ */