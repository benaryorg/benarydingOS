#include "../header.h"

int memtest(const int arrs,const int bytes)
{
	int **f=malloc(sizeof(int *)*arrs);
	int i,j;
	for(i=0;i<arrs;i++)
	{
		f[i]=malloc(sizeof(int)*bytes);
		for(j=0;j<bytes;j++)
		{
			f[i][j]=j%256;
		}
	}

	for(i=0;i<arrs;i++)
	{
		for(j=0;j<bytes;j++)
		{
			if(f[i][j]!=j%256)
			{
				return 1;
			}
		}
		free(f[i]);
	}
	
	return 0;
}
