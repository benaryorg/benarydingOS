#ifndef __BENARYDINGOS_HEADER__
#define __BEANRYDINGOS_HEADER__

#include "syscalls.h"
#include "stdargs.h"
#include "stdint.h"
#include "multiboot.h"
#include "memory.h"
#include "utils.h"
#include "color.h"
#include "ctype.h"
#include "string.h"
#include "gdt.h"
#include "idt.h"
#include "interrupt_handler.h"
#include "pic.h"
#include "tss.h"
#include "elf.h"

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
void setcursor(uint16_t);

#endif
