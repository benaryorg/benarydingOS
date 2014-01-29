#include "header.h"

void movelinesup(void)
{
	memcpy(BUFFER_TEXT,BUFFER_TEXT+BUFFER_TEXT_WIDTH*2,(BUFFER_TEXT_HEIGHT-1)*BUFFER_TEXT_WIDTH*2);
	memset(BUFFER_TEXT+BUFFER_TEXT_WIDTH*(BUFFER_TEXT_HEIGHT-1)*2,0,BUFFER_TEXT_WIDTH*2);
	int i;
	for(i=0;i<BUFFER_TEXT_WIDTH;i++)
	{
		*(BUFFER_TEXT+(BUFFER_TEXT_HEIGHT-1)*BUFFER_TEXT_WIDTH*2+i*2+1)=getcolor();
	}
}

void cleardisplay(void)
{
	size_t i;
	for(i=0;i<BUFFER_TEXT_HEIGHT*BUFFER_TEXT_WIDTH*2;i++)
	{
		*(BUFFER_TEXT+i)=(i%2)?getcolor():0;
	}
	resetposition();
}
