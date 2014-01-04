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

void memdump(void)
{
	int i;
	mem_allocated_t *tile;
	for(i=0;i<MEM_STACK_SIZE;i++)
	{
		tile=physmemgetallocation(i);
		if(tile->start||tile->end)
		{
			printf("%d: %p-%p\n",i,tile->start,tile->end);
		}
	}
}

