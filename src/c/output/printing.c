#include "../header.h"

int putchar(int c)
{
	int position=getposition();

	unsigned char ch=(unsigned char)c;

	if(position>BUFFER_TEXT_WIDTH*BUFFER_TEXT_HEIGHT)
	{
		position-=BUFFER_TEXT_WIDTH;
		movelinesup();
	}

	switch(ch)
	{
		case '\n':
			position+=BUFFER_TEXT_WIDTH-position%BUFFER_TEXT_WIDTH;
			break;
		case '\t':
			position+=5-position%5;
			break;
		case '\r':
			position-=position%BUFFER_TEXT_WIDTH;
			break;
		case '\b':
			position--;
			break;
		default:
			*(BUFFER_TEXT+position*2)=ch;
			*(BUFFER_TEXT+position*2+1)=getcolor();
			position++;
			break;
	}
	setposition(position);
	return c;
}

size_t printint(int i)
{
	size_t n=0;
	if(i<0)
	{
		putchar('-');
		i=-i;
		n++;
	}
	if(i==0)
	{
		putchar('0');
		n++;
	}
	else
	{
		int x;
		for(x=1;x<=i;x*=10);
		x/=10;
		for(;x;x/=10)
		{
			putchar((char)('0'+(i/x)));
			i-=x*(i/x);
			n++;
		}
	}
	return n;
}

int puts(const char *s)
{
	int i;
	for(i=0;s[i];i++)
	{
		putchar(s[i]);
	}
	putchar('\n');
	return (int)i+2;
}
