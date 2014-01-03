#include "../header.h"

static const char digits[] = "0123456789ABCDEF";

/* this is a real one-liner. if you can manage to make it less readable, don't hesitate to do so */
size_t strlen(const char *s) {
	size_t len = 0; const char *p = s; for (; *p; p++, len++); return len;
}

const char *itoa (int value, char *str, int base) {
	int i, j, pos = 0;
	char c;
	
	if (base > 16 || base < 2) { /* can't work with bases less than 2 or greater than 16, sorry! */
		base = 10; /* let's set the base to 10 then */
	}
	
	if (value < 0) { /* the number is negative! */
		str[pos++] = '-';
		value *= -1; /* and now it's not. what kind of black magic is this? */
	}
	
	if (!value) { /* the number is 0 */
		str[pos++] = digits[0];
	} else {
		while (value) {
			str[pos++] = digits[value % base];
			value /= base;
		}
	}
	
	str[pos++] = 0x00; /* don't forget to add the string delimiter! */
	
	/* reverse the string */
	for (i = 0, j = strlen(str) - 1; i < j; i++, j--) {
		c = str[i];
		str[i] = str[j];
		str[j] = c;
	}
	
	return str;
}