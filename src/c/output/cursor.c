#include "../header.h"

int cursorposition(int data,char set)
{
	static int pos=0;
	if(set)
	{
		pos=data;
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
