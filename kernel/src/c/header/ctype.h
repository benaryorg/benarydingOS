/* ctype.h - character types */

#ifndef __CTYPE_H_DEFINED__
#define __CTYPE_H_DEFINED__

#include "../header.h"

/* character classification routines */
int isalnum(int);
int isalpha(int);
int isascii(int);
int isblank(int);
int iscntrl(int);
int isdigit(int);
int isgraph(int);
int islower(int);
int isprint(int);
int ispunct(int);
int isspace(int);
int isupper(int);
int isxdigit(int);

/* convert character to ASCII */
int toascii(int);

/* converts letter to upper or lower case */
int toupper(int);
int tolower(int);

#endif /* __CTYPE_H_DEFINED__ */