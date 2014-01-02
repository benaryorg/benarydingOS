#include "header.h"

int main(void)
{
	int i,j;
	for(i=0;i<100;i++)
		for(j=0;j<BUFFER_TEXT_WIDTH;j++)
			putchar('0'+(i+j)%10);
	return 0;
}
