#include "header.h"

int main(void)
{
	cleardisplay();
	puts("BenarydingOS Running!");
	puts("Memorydump:");
	memdump();
// 	cleardisplay();
// 	int i;
// 	for(i=1;i<24;i++)
// 	{
// 		printf("%d  ",i);
// 	}
	printf("\n-1 in hex: %x\n",-1);
	printf("-32 in hex: %x\n",-32);
	printf("-32 in binary: %b\n",-32);
	printf("\n1 in hex: %x\n",1);
	printf("32 in hex: %x\n",32);
	printf("32 in binary: %b\n",32);
	return 0;
}
