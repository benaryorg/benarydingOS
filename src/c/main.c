#include "header.h"

int init(multiboot_info_t *mb_info)
{
	cleardisplay();

	printf("Started\n");

	physmeminit(mb_info);

	printf("Inited\n");

	int *f[10]={};
	int i,j;
	for(i=0;i<10;i++)
	{
		f[i]=malloc(sizeof(int)*100);

		printf("Allocated %d\n",i);

		for(j=0;j<100;j++)
		{
			f[i][j]=j;
		}
	}

	for(i=0;i<10;i++)
	{
		for(j=0;j<100;j++)
		{
			if(f[i][j]!=j)
			{
				printf("Fehler\n");
			}
		}
	}

	printf("Hello, world!\n");
	
	return 0;
}
