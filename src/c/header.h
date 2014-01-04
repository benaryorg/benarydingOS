#ifndef __BENARYDINGOS_HEADER__
#define __BEANRYDINGOS_HEADER__

#include "header/stdargs.h"
#include "header/stdtype.h"
#include "header/multiboot.h"
#include "header/memory.h"
#include "header/utils.h"
#include "header/color.h"
#include "header/ctype.h"

#define BUFFER_TEXT ((char *)0xb8000)
#define BUFFER_TEXT_WIDTH 80
#define BUFFER_TEXT_HEIGHT 25

int main(void);

int putchar(int);
void movelinesup(void);
int printf(const char *format,...);
void kprintf(const char *format,...);
size_t printint(int);
size_t printdouble(double);
void cleardisplay(void);
int puts(const char *);
void setposition(int);
int getposition(void);
void resetposition(void);
int cursorposition(int,char);

#endif
