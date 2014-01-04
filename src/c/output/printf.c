#include "../header.h"

int printf(const char *format,...)
{
	const char *p;
	int i, count = 0;
	char *s;
	char buf[256];
	
	va_list list;
	va_start(list,format);
	
	for (p = format; *p != 0x00; p++) {
		if (*p != '%') {
			putchar(*p);
			count++;
		}
		else {
			switch (*++p) {
				case 'c': /* character */
					i = va_arg(list, int);
					putchar(i);
					count++;
					break;
				
				case 'd': /* integer */
					i = va_arg(list, int);
					itoa(i, buf, 10);
					for(i = 0; buf[i]; i++) {
						putchar(buf[i]);
						count++;
					}
					break;
				
				case 'x': /* heXXX */
					i = va_arg(list, int);
					itoa(i, buf, 16);
					for(i = 0; buf[i]; i++) {
						putchar(buf[i]);
						count++;
					}
					break;
				
				case 's': /* string */
					s = va_arg(list, char*);
					for(i = 0; s[i]; i++) {
						putchar(s[i]);
						count++;
					}
					break;
				
				case 'b': /* we binary now! */
					i = va_arg(list, int);
					itoa(i, buf, 2);
					for(i = 0; buf[i]; i++) {
						putchar(buf[i]);
						count++;
					}
					break;
					
				case 'o': /* also octal! */
					i = va_arg(list, int);
					itoa(i, buf, 8);
					for(i = 0; buf[i]; i++) {
						putchar(buf[i]);
						count++;
					}
					break;
				
				case '%': /* percent */
					putchar('%');
					count++;
					break;
			}
		}
	}

	va_end(list);
	return count;
}
