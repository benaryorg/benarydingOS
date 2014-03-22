#include "header.h"

int printf(const char *format,...)
{
	const char *p;
	int i, j, npos, count = 0;
	char *s;
	char buf[256];
	
	int pad_with_zeros = 0;
	
	va_list list;
	va_start(list,format);
	
	for (p = format; *p != 0x00; p++) {
		if (*p != '%') {
			putchar(*p);
			count++;
		}
		else {
			pad_with_zeros = npos = j = i = 0;
			++p;
			while (isdigit(*p)) { /* we have a number to parse!  */
				npos++;
				if (*p == '0' && npos == 1) {
					pad_with_zeros = 1;
					++p;
					continue;
				}
				
				buf[npos - (pad_with_zeros ? 2 : 1)] = *p;
				++p;
			}
			if (npos) {
				buf[npos] = 0;
				j = atoi(buf);
				buf[0] = 0;
			}
			switch (*p) {
				case 'c': /* character */
					i = va_arg(list, int);
					if (npos) {
						for (npos = 0; npos < j; npos++) {
							putchar(' ');
							count++;
						}
					}
					putchar(i);
					count++;
					break;
				
				case 'd': /* integer */
					i = va_arg(list, int);
					itoa(i, buf, 10);
					if (npos) {
						j -= strlen(buf);
						for (npos = 0; npos < j; npos++) {
							putchar(pad_with_zeros ? '0' : ' ');
							count++;
						}
					}
					for(i = 0; buf[i]; i++) {
						putchar(buf[i]);
						count++;
					}
					break;

				case 'u': /* unsigned integer */
					i = va_arg(list, int);
					uitoa(i, buf, 10);
					if (npos) {
						j -= strlen(buf);
						for (npos = 0; npos < j; npos++) {
							putchar(pad_with_zeros ? '0' : ' ');
							count++;
						}
					}
					for(i = 0; buf[i]; i++) {
						putchar(buf[i]);
						count++;
					}
					break;
				

				case 'x': /* heXXX */
					i = va_arg(list, int);
					uitoa(i, buf, 16);
					if (npos) {
						j -= strlen(buf);
						for (npos = 0; npos < j; npos++) {
							putchar(pad_with_zeros ? '0' : ' ');
							count++;
						}
					}
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
					uitoa(i, buf, 2);
					if (npos) {
						j -= strlen(buf);
						for (npos = 0; npos < j; npos++) {
							putchar(pad_with_zeros ? '0' : ' ');
							count++;
						}
					}
					for(i = 0; buf[i]; i++) {
						putchar(buf[i]);
						count++;
					}
					break;
					
				case 'o': /* also octal! */
					i = va_arg(list, int);
					uitoa(i, buf, 8);
					if (npos) {
						j -= strlen(buf);
						for (npos = 0; npos < j; npos++) {
							putchar(pad_with_zeros ? '0' : ' ');
							count++;
						}
					}
					for(i = 0; buf[i]; i++) {
						putchar(buf[i]);
						count++;
					}
					break;
				
				case 'p': /* pointers */
					i = (int)va_arg(list, void *);
					uitoa(i, buf, 16);
					if (npos) {
						j -= strlen(buf);
						for (npos = 0; npos < j; npos++) {
							putchar(pad_with_zeros ? '0' : ' ');
							count++;
						}
					}
					for (i = 0; buf[i]; i++) {
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
