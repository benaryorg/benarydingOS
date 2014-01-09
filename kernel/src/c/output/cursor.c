#include "../header.h"

int cursorposition(int data,char set)
{
	static int pos=0;
	if(set)
	{
		pos=data;
		setcursor(pos);
	}
	else
	{
		return pos;
	}
	return 0;
}

int getposition(void)
{
	return cursorposition(0,0);
}

void setposition(int position)
{
	cursorposition(position,1);
}

void resetposition(void)
{
	setposition(0);
}

void setcursor(uint16_t pos)
{
	outb(0x3D4,14);
	outb(0x3D5,pos>>8);
	outb(0x3D4,15);
	outb(0x3D5,pos);
}
