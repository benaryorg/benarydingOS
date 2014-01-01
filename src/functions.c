#include "header.h"

void kputchar(char ch)
{
	static int position=0;

	if(position>BUFFER_TEXT_WIDTH*BUFFER_TEXT_HEIGHT)
	{
		position=BUFFER_TEXT_WIDTH*(BUFFER_TEXT_HEIGHT-1);
		movelinesup();
	}

	*(BUFFER_TEXT+position)=ch;
	*(BUFFER_TEXT+position+1)=getcolor();
	position+=2;
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
	int i,j;
	for(i=0;i<BUFFER_TEXT_HEIGHT-1;i++)
	{
		for(j=0;j<BUFFER_TEXT_WIDTH*2;j++)
		{
			*(BUFFER_TEXT+i*BUFFER_TEXT_WIDTH*2+j)=*(BUFFER_TEXT+(i+1)*BUFFER_TEXT_WIDTH+j);
		}
	}
	for(i=0;i<BUFFER_TEXT_WIDTH*2;i++)
	{
		*(BUFFER_TEXT+(BUFFER_TEXT_HEIGHT-1)*BUFFER_TEXT_WIDTH*2+i)=0;
	}
}
