#include "../header.h"

void movelinesup(void)
{
	int i;
	for(i=0;i<BUFFER_TEXT_HEIGHT-1;i++)
	{
		memcpy(BUFFER_TEXT+i*BUFFER_TEXT_WIDTH*2,BUFFER_TEXT+(i+1)*BUFFER_TEXT_WIDTH*2,BUFFER_TEXT_WIDTH*2);
	}
	memset(BUFFER_TEXT+BUFFER_TEXT_WIDTH*(BUFFER_TEXT_HEIGHT-1)*2,0,BUFFER_TEXT_WIDTH*2);
}
