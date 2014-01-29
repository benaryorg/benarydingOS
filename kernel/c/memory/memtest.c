#include "../header.h"

int memtest(const int arrs,const int bytes)
{
	unsigned char **f=malloc(sizeof(unsigned char *)*arrs);
	int i,j;
	for(i=0;i<arrs;i++)
	{
		
		f[i]=malloc(sizeof(unsigned char)*bytes);
		if(!f[i])
		{
			printf("Got no more Memory @arr=%d\n",i);
			break;
		}
		for(j=0;j<bytes;j++)
		{
			f[i][j]=j%256;
		}
	}

	for(i=0;i<arrs;i++)
	{
		if(f[i])
		{
			for(j=0;j<bytes;j++)
			{
				if(f[i][j]!=j%256)
				{
					printf("%d/%d=%d\n",i,j,f[i][j]);
					printf("%p/%p\n",f[i-1],f[i]);
					return 1;
				}
			}
			free(f[i]);
		}
	}
	return 0;
}

void memdump(void)
{
	int i;
	mem_allocation_t *tile;
	for(i=0;i<MEM_STACK_SIZE;i++)
	{
		tile=physmemgetallocation(i);
		if(tile->start||tile->end)
		{
			printf("%10d: %10p-%10p\n",i,tile->start,tile->end);
		}
	}
}

