#include "header.h"

/**
 * Creates a 8 bit color value from a background and foreground color
 *
 * @param bg Backgroundcolor (enum)
 * @param fg Foregroundcolor (enum)
 * @return 8 bit color value
 *
 */
uint8_t _color_pair(enum hw_color bg, enum hw_color fg) {
	return bg << 4 | fg;
}

/**
 * The function for handling the console color variable (internal DO NOT USE DIRECTLY)
 *
 * @param data The color (8 bit value)
 * @param set Tells the function if the color should get returned (0), reseted (-1) or set(not -1 or 0)
 * @return If set==0 the actual color, else 0
 */
unsigned char color(char data, char set)
{
	/* default colour: light gray on black */
	static char color=DEFAULTCOLOR;
	
	if(set)
	{
		if(set==-1)
		{
            //Reset
			color=DEFAULTCOLOR;
		}
		else
		{
            //Set
			color=data;
		}
	}
	else
	{
        //Return
		return color;
	}
	return 0;
}
/**
 * The frontend function for getting the console color
 *
 * @return The color
 */
unsigned char getcolor(void)
{
    //Data=0, Set=0 -> Return
	return color(0,0);
}

/**
 * The frontend function for setting the console color
 *
 * @param data What color to set (8 bit value)
 */
void setcolor(char data)
{
    //Data=data, Set=1 -> Set
	color(data,1);
}

/**
 * The frontend function for setting the console foreground color
 *
 * @param data Enum value of foregroundcolor
 */
void setfgcolor(enum hw_color data)
{
	color(((getcolor()>>4)<<4)|((data<<4)>>4),1);
}

/**
 * The frontend function for setting the console background color
 *
 * @param data Enum value of backgroundcolor
 */
void setbgcolor(enum hw_color data)
{
	color((getcolor()>>4)|(data<<4),1);
}

/**
 * The frontend function for resetting the console color
 */
void resetcolor(void)
{
	color(0,-1);
}
