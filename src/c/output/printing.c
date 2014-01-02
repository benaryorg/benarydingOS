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
	do
	{
		kputchar((char)('0'+i%10));
		n++;
	}while(i/=10);
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
	for(va_start(list,format);*format,format++)
	{
		if(*format=='%')
		{
			switch(*++format)
			{
				case '%':
					kputchar('%');
					break;
				case 'd':
					i=(int)va_arg(list,int);
					printint(i);
				default:
#warning Unknown symbol after '%'
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
