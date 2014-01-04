#include "../header.h"

int putchar(int c)
{
	int position=getposition();

	unsigned char ch=(unsigned char)c;

	if(position>=BUFFER_TEXT_WIDTH*BUFFER_TEXT_HEIGHT)
	{
		position=BUFFER_TEXT_WIDTH*(BUFFER_TEXT_HEIGHT-1);
		setposition(position);
		movelinesup();
	}

	switch(ch)
	{
		case '\n':
			position+=BUFFER_TEXT_WIDTH-position%BUFFER_TEXT_WIDTH;
			break;
		case '\t':
			position+=5-position%5;
			break;
		case '\r':
			position-=position%BUFFER_TEXT_WIDTH;
			break;
		case '\b':
			position--;
			break;
		default:
			*(BUFFER_TEXT+position*2)=ch;
			*(BUFFER_TEXT+position*2+1)=getcolor();
			position++;
			break;
	}
	setposition(position);
	return c;
}

size_t printint(int i)
{
	size_t n=0;
	if(i<0)
	{
		putchar('-');
		i=-i;
		n++;
	}
	if(i==0)
	{
		putchar('0');
		n++;
	}
	else
	{
		int x;
		for(x=1;x<=i;x*=10);
		x/=10;
		for(;x;x/=10)
		{
			putchar((char)('0'+(i/x)));
			i-=x*(i/x);
			n++;
		}
	}
	return n;
}

int puts(const char *s)
{
	int i;
	for(i=0;s[i];i++)
	{
		putchar(s[i]);
	}
	putchar('\n');
	return (int)i+2;
}

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
