#include "../header.h"

void *memcpy(void *dest,const void *src,unsigned int n)
{
	size_t i;
	for(i=0;i<n;i++)
	{
		*((unsigned char *)dest+i)=*((const unsigned char *)src+i);
	}
	return dest;
}

void *memset(void *data,int byte,unsigned int n)
{
	size_t i;
	for(i=0;i<n;i++)
	{
		*((char *)data+i)=(char)byte;
	}
	return data;
}
