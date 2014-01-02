#include "../header.h"

void kputchar(char ch)
{
	static int position=0;

	if(position>BUFFER_TEXT_WIDTH*BUFFER_TEXT_HEIGHT)
	{
		movelinesup();
		position=BUFFER_TEXT_WIDTH*(BUFFER_TEXT_HEIGHT-1)+1;
	}

	*(BUFFER_TEXT+position*2)=ch;
	*(BUFFER_TEXT+position*2+1)=getcolor();
	position++;
}

size_t printint(int i)
{
	size_t n=0;
	if(i<0)
	{
		kputchar('-');
		i=-i;
		n++;
	}
	int x;
	for(x=1;x<=i;x*=10);
	x/=10;
	for(;x;x/=10)
	{
		kputchar((char)('0'+(i/x)));
		i-=x*(i/x);
		n++;
	}
	return n;
}

size_t printdouble(double d)
{
	size_t n=0;
	if(d<0)
	{
		kputchar('-');
		d=-d;
		n++;
	}
	int x;
	int i=(int)d;
	d-=i;
	for(x=1;x<=i;x*=10);
	x/=10;
	for(;x;x/=10)
	{
		kputchar((char)('0'+(i/x)));
		i-=x*(i/x);
		n++;
	}
	kputchar('.');
	n++;
	for(i=0;i<6;i++)
	{
		kputchar((char)('0'+((int)(d*=10))%10));
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
	void *ptr;

	va_list list;
	for(va_start(list,format);*format;format++)
	{
		if(*format=='%')
		{
			switch(*++format)
			{
				case '%':
					kputchar('%');
					break;
				case 'i':
					i=(int)va_arg(list,int);
					printint(i);
					break;
				case 'd':
					d=(double)va_arg(list,double);
					printdouble(d);
					break;
				default:
//#warning Unknown symbol after '%'
				break;
			}
		}
		else
		{
			kputchar(*format);
		}
	}
	va_end(list);
}

int printf(const char *format,...)
{
	va_list list;
	va_start(list,format);
	va_arg(list,int);
	while(0)
	{
		
	}
	va_end(list);
	return 0;//Upon successful return, these functions return the number of characters printed (excluding the null byte used to end output to strings).
}
