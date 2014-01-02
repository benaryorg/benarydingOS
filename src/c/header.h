#ifndef __BENARYDINGOS_HEADER__
#define __BEANRYDINGOS_HEADER__

#include "header/stdargs.h"
#include "header/stdtype.h"

#define BUFFER_TEXT ((char *)0xb8000)
#define BUFFER_TEXT_WIDTH 80
#define BUFFER_TEXT_HEIGHT 25

void kputchar(char);
char color(char,char);
void setcolor(char);
char getcolor(void);
void movelinesup(void);
void *memcpy(void *,const void *,size_t);
void *memset(void *,int,size_t);
int printf(const char *format,...);
int kprintf(const char *format,...);

#endif
