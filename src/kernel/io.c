#include "header.h"

inline void outb(uint16_t port,uint8_t data)
{
	asm volatile("outb %0, %1" : : "a" (data), "Nd" (port));
}

inline unsigned char inb(uint16_t port)
{
	unsigned char ret;
	asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
	return ret;
}
