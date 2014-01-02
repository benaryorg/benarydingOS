#include "../header.h"

int printf(const char *format,...)
{
	const char *p;
	int i, count = 0;
	char *s;
	
	va_list list;
	va_start(list,format);
	
	for (p = format; *p != 0x00; p++) {
		if (*p != '%') {
			putchar(*p);
			count++;
			continue;
		}
		
		switch (*++p) {
			case 'c':
				i = va_arg(list, int);
				putchar(i);
				count++;
				break;
			
			case 's':
				s = va_arg(list, char*);
				for(i = 0; s[i]; i++) {
					putchar(s[i]);
					count++;
				}
				break;
			
			case '%':
				putchar('%');
				count++;
				break;
		}
	}
	
	va_arg(list,int);
	
	va_end(list);
	return count;
}
