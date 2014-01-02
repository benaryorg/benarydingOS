#include "../header.h"

int printf(const char *format,...)
{
	const char *p;
	va_list list;
	va_start(list,format);
	
	for (p = format; *p != 0x00; p++) {
		
	}
	
	va_arg(list,int);
	
	va_end(list);
	return 0;//Upon successful return, these functions return the number of characters printed (excluding the null byte used to end output to strings).
}
