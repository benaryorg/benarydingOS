#include "header/stdint.h"

void _start(void)
{
	int i;
	while(1)
		for(i=0;i<10;i++)
			asm("int $0x30"::"a"(0),"b"('0'+i));
	while(1);
}
