#include "../header.h"

uint8_t _color_pair(enum hw_color bg, enum hw_color fg) {
	return bg << 4 | fg;
}

char color(char data, char set)
{
	/* default colour: light gray on black */
	static char color=DEFAULTCOLOR;
	
	if(set)
	{
		if(set==-1)
		{
			color=DEFAULTCOLOR;
		}
		else
		{
			color=data;
		}
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

void setfgcolor(enum hw_color data)
{
	color(((getcolor()>>4)<<4)+((data<<4)>>4),1);
}

void setbgcolor(enum hw_color data)
{
	color((getcolor()>>4)+(data<<4),1);
}

void resetcolor(void)
{
	color(0,-1);
}
