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
