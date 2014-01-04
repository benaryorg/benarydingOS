#include "../header.h"

void movelinesup(void)
{
	memcpy(BUFFER_TEXT,BUFFER_TEXT+BUFFER_TEXT_WIDTH*2,(BUFFER_TEXT_HEIGHT-1)*BUFFER_TEXT_WIDTH*2);
	memset(BUFFER_TEXT+BUFFER_TEXT_WIDTH*(BUFFER_TEXT_HEIGHT-1)*2,0,BUFFER_TEXT_WIDTH*2);
	putchar(' ');
	putchar('\b');
}

void cleardisplay(void)
{
	size_t i;
	for(i=0;i<BUFFER_TEXT_HEIGHT*BUFFER_TEXT_WIDTH*2;i++)
	{
		*(BUFFER_TEXT+i)=0;
	}
	resetposition();
}
