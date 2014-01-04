#ifndef __UTILS_HEADER__
#define __UTILS_HEADER__

static const char digits[] = "0123456789ABCDEF";

/* stdlib */
int atoi (const char *nptr);

/* math */
int _pow(int a, int b);

/* string functions */
size_t strlen (const char *s);

/* nonstandard extensions, fuck yeah! */
const char *itoa (int value, char *str, int base);
const char *uitoa (unsigned int value, char *str, int base);

#endif
