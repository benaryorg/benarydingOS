#include "../header.h"

void kprintf(const char *format,...)
{
	char c;
	int i;
	char *cp;

	va_list list;
	for(va_start(list,format);*format;format++)
	{
		if(*format=='%')
		{
			switch(*++format)
			{
				case '%':
					putchar('%');
					break;
				case 'i':
					i=(int)va_arg(list,int);
					printint(i);
					break;
				case 'c':
					c=(char)va_arg(list,int);
					putchar(c);
					break;
				case 's':
					cp=(char *)va_arg(list,char *);
					while(*cp)
					{
						putchar(*cp++);
					}
					break;
				default:
//#warning Unknown symbol after '%'
				break;
			}
		}
		else
		{
			putchar(*format);
		}
	}
	va_end(list);
}


