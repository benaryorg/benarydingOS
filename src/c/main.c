#include "header.h"

int main(void)
{
	cleardisplay();
	int i,j;
	for(i=0;i<35;i++)
		for(j=0;j<80;j++)
			putchar('0'+(i+j)%10);
	return 0;
}
