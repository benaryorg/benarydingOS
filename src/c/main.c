#include "header.h"

int main(void)
{
	cleardisplay();
	puts("BenarydingOS Running!");
	puts("Memorydump:");
	memdump();
	cleardisplay();
	int i;
	for(i=1;i<24;i++)
	{
		printf("%d\n",i);
	}
	return 0;
}
