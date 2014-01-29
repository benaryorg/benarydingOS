#include "../header.h"

void haltcpu(void)
{
	while(1)
	{
		asm volatile("cli;hlt\n");
	}
}

void kernelpanic(const char *str)
{
	char s[256] = "Kernel Panic: ";
	strcat(s, str);
	setfgcolor(COLOR_LIGHT_RED);
	puts(s);
	resetcolor();
	haltcpu();
}

void register_reload(void)
{
	asm volatile
	(
		"mov $0x10, %ax\n"
		"mov %ax, %ds\n"
		"mov %ax, %es\n"
		"mov %ax, %fs\n"
		"mov %ax, %gs\n"
		"mov %ax, %ss\n"
//		"ljmp $0x8, $.1\n"
//		".1:\n"
	);
}

/* inefficient and nonstandard pow() */
int _pow(int a, int b) {
	int i;
	int retval = 1;
	for (i = 0; i < b; i++) {
		retval *= a;
	}
	return retval;
}

/* converts the string pointed to by nptr to int. */
int atoi (const char *nptr) {
	int i, len, retval = 0;
	len = strlen(nptr);
	for (i = 0; i < len; i++) {
		if (isdigit(nptr[i])) {
			retval += (nptr[i] - '0') * (_pow(10, len - i - 1));
		} else {
			break;
		}
	}
	return retval;
}

const char *itoa (int value, char *str, int base) {
	int i, j, pos = 0;
	char c;
	
	if (base > 16 || base < 2) { /* can't work with bases less than 2 or greater than 16, sorry! */
		base = 10; /* let's set the base to 10 then */
	}
	
	if (value < 0) { /* the number is negative! */
			str[pos++] = '-';
			value *= -1; /* and now it's not anymore. what kind of black magic is this? */
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

const char *uitoa (unsigned int value, char *str, int base) {
	int i, j, pos = 0;
	char c;
	
	if (base > 16 || base < 2) { /* can't work with bases less than 2 or greater than 16, sorry! */
		base = 10; /* let's set the base to 10 then */
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
