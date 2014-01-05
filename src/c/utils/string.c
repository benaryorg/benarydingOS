#include "../header.h"

/* this is a real one-liner. if you can manage to make it less readable, don't hesitate to do so */
size_t strlen(const char *s) {
	size_t len = 0; while (s[len]) len++; return len;
}

/* the strcat */
char* strcat(char* dest, const char* src) {
	char *retp = dest;
	
	while (*dest) {
		dest++;
	}
	while ((*dest++ = *src++)) {
	}
	
	return retp;
}