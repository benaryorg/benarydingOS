#include "header.h"

int main(void)
{
	int *f[10]={};
	int i,j;
	for(i=0;i<10;i++)
	{
		f[i]=malloc(sizeof(int)*100);
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
		free(f[i]);
	}

	printf("Hello, world!\n");
	
	return 0;
}
