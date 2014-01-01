#include "header.h"

void init(void)
{
	int i;
	while(1)
	{
		for(i=0;i<26;i++)
		{
			kputchar('a'+i);
		}
	}
}
