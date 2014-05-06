#include "header.h"

/**
 * outb C-function for sending data to ports
 * 
 * @param port The port
 * @param data The data
 */
inline void outb(uint16_t port,uint8_t data)
{
	asm volatile("outb %0, %1" : : "a" (data), "Nd" (port));
}

/**
 * inb C-function for receiving data from a port
 * @param port The port
 * @return The data received
 */
inline unsigned char inb(uint16_t port)
{
	unsigned char ret;
	asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
	return ret;
}
