#include "../header.h"

inline void outb(uint16_t port,uint8_t data)
{
	asm volatile("outb %0, %1" : : "a" (data), "Nd" (port));
}
