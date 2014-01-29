#include "header.h"

int isalnum(int c) {
	return (isalpha(c) || isdigit(c));
}

int isalpha(int c) {
	return (isupper(c) || islower(c));
}

int isdigit(int c) {
	return (c >= '0' && c <= '9');
}

int isupper(int c) {
	return (c >= 'A' && c <= 'Z');
}

int islower(int c) {
	return (c >= 'a' && c <= 'z');
}

int isspace(int c) {
	return (c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v');
}

int isascii(int c) {
	return (c >= 0x00 && c <= 0x7F);
}

int isblank(int c) {
	return (c == ' ' || c == '\t');
}

int iscntrl(int c) {
	return 0;
}

int isxdigit(int c) {
	int i;
	c = toupper(c);
	for (i = 0; i < 16; i++) {
		if (c == digits[i]) {
			return 1;
		}
	}
	return 0;
}

int toupper(int c) {
	if (islower(c)) {
		return c - 32;
	}
	return c;
}

int tolower(int c) {
	if (isupper(c)) {
		return c + 32;
	}
	return c;
}

/* too lazy to implement all of them now. sorry! */
int toascii(int c) {
	return c;
}

int isgraph(int c) {
	return 0;
}

int isprint(int c) {
	return 0;
}

int ispunct(int c) {
	return 0;
}
