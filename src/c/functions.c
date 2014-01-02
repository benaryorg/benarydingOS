#include "header.h"

void kputchar(char ch)
{
	static int position=0;

	if(position>BUFFER_TEXT_WIDTH*BUFFER_TEXT_HEIGHT)
	{
		movelinesup();
//		position=BUFFER_TEXT_WIDTH*(BUFFER_TEXT_HEIGHT-1)+1;
		position=0;
	}

	*(BUFFER_TEXT+position*2)=ch;
	*(BUFFER_TEXT+position*2+1)=getcolor();
	position++;
}

char color(char data,char set)
{
	static char color=(char)0x0a;
	if(set)
	{
		color=data;
	}
	else
	{
		return color;
	}
	return 0;
}

char getcolor(void)
{
	return color(0,0);
}

void setcolor(char data)
{
	color(data,1);
}

void movelinesup(void)
{
/*
	int i;
	for(i=0;i<BUFFER_TEXT_HEIGHT-1;i++)
	{
		memcpy(BUFFER_TEXT+i*BUFFER_TEXT_WIDTH*2,BUFFER_TEXT+(i+1)*BUFFER_TEXT_WIDTH*2,BUFFER_TEXT_WIDTH*2);
	}
	memset(BUFFER_TEXT+BUFFER_TEXT_WIDTH*(BUFFER_TEXT_HEIGHT-1)*2,0,BUFFER_TEXT_WIDTH*2);
*/
	memset(BUFFER_TEXT,0,BUFFER_TEXT_WIDTH*BUFFER_TEXT_HEIGHT*2);
}

void *memcpy(void *dest,const void *src,size_t n)
{
	size_t i;
	for(i=0;i<n;i++)
	{
		*((char *)dest+i)=*((const char *)src+i);
	}
	return dest;
}

void *memset(void *data,int byte,size_t n)
{
	size_t i;
	for(i=0;i<n;i++)
	{
		*((char *)data+i)=(char)byte;
	}
	return data;
}

int printf(const char *format,...)
{
	va_list list;
	va_start(list,format);
	va_arg(list,int);
	while(*format++)
	{
		
	}
	va_end(list);
	return 0;//Upon successful return, these functions return the number of characters printed (excluding the null byte used to end output to strings).
}
