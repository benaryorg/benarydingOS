#include "header.h"

void init(void)
{
	cleardisplay();
	int i,j;
	for(i=0;i<5;i++)
	{
		for(j=0;j<i;j++)
		{
			putchar('\t');
		}
		kprintf("%i\n",i);
	}
}
