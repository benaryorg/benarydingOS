#include "../header.h"

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
