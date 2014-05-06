#include "header.h"

/**
 * Internal function for handling the console cursor position (DO NOT USE DIRECTLY)
 *
 * @param data The offset from the first character
 * @param set Tells the function if the position should get returned (0), set(not 0)
 * @return If set==0 the actual position, else 0
 */
int cursorposition(int data,char set)
{
	static int pos=0;
	if(set)
	{
        //Set
		pos=data;
        //Set the cursor on the display
		setcursor(pos);
	}
	else
	{
        //Return
		return pos;
	}
	return 0;
}

/**
 * Frontend function for getting the cursor position
 *
 * @return The position
 */
int getposition(void)
{
	return cursorposition(0,0);
}

/**
 * Frontend function for setting the cursor position
 *
 * @param position The offset from the first character
 */
void setposition(int position)
{
	cursorposition(position,1);
}

/**
 * Set the cursor to the first character
 */
void resetposition(void)
{
	setposition(0);
}

/**
 * Function for setting the cursor on the display
 *
 * @param pos The position
 */
void setcursor(uint16_t pos)
{
	outb(0x3D4,14);
	outb(0x3D5,pos>>8);
	outb(0x3D4,15);
	outb(0x3D5,pos);
}
