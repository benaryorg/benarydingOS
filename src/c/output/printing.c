#include "../header.h"

int putchar(int c)
{
	static int position=0;

	unsigned char ch=(unsigned char)c;

	if(position>BUFFER_TEXT_WIDTH*BUFFER_TEXT_HEIGHT)
	{
		position-=BUFFER_TEXT_WIDTH;
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

size_t printdouble(double d)
{
	size_t n=0;
	if(d<0)
	{
		putchar('-');
		d=-d;
		n++;
	}
	int i=(int)d;
	d-=i;
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
	putchar('.');
	n++;
	for(i=0;i<6;i++)
	{
		putchar((char)('0'+((int)(d*=10))%10));
		n++;
	}
	return n;
}

void kprintf(const char *format,...)
{
	char c;
	int i;
	double d;
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
				case 'd':
					d=(double)va_arg(list,double);
					printdouble(d);
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
