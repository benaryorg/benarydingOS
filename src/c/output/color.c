#include "../header.h"

/* hardware text mode colours */
enum hw_color {
	COLOR_BLACK         = 0x0,
	COLOR_BLUE          = 0x1,
	COLOR_GREEN         = 0x2,
	COLOR_CYAN          = 0x3,
	COLOR_RED           = 0x4,
	COLOR_MAGENTA       = 0x5,
	COLOR_ORANGE        = 0x6,
	COLOR_LIGHT_GRAY    = 0x7,
	COLOR_DARK_GRAY     = 0x8,
	COLOR_LIGHT_BLUE    = 0x9,
	COLOR_LIGHT_GREEN   = 0xa,
	COLOR_LIGHT_CYAN    = 0xb,
	COLOR_LIGHT_RED     = 0xc,
	COLOR_LIGHT_MAGENTA = 0xd,
	COLOR_YELLOW        = 0xe,
	COLOR_WHITE         = 0xf,
};

uint8_t _color_pair(enum hw_color bg, enum hw_color fg) {
	return bg << 4 | fg;
}

char color(char data, char set)
{
	/* default colour: light gray on black */
	static char color = 0x07;
	
	if(set)
	{
		color=data;
	}
	else
	{
		return color;
	}
	return 0;
}

char getcolor(void)
{
	return color(0,0);
}

void setcolor(char data)
{
	color(data,1);
}
