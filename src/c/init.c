#include "header.h"

void init(void)
{
	kprintf("%s%c","test",'\n');
	puts("asdf");
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
