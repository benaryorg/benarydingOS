#include "header.h"

void init(void)
{
	int i,j;
	for(i=0;i<30;i++)
	{
		for(j=0;j<80;j++)
		{
			kputchar('0'+(i+j)%10);
		}
	}
}
