#include "header.h"

int main(void)
{
	cleardisplay();
	puts("BenarydingOS Running!");
	puts("Memorydump:");
	memdump();
	cleardisplay();
	int i;
	for(i=1;i<9999;i++)
	{
		printf("%d",i%9);
	}
	return 0;
}
