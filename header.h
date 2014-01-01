#ifndef __BENARYDINGOS_HEADER__
#define __BEANRYDINGOS_HEADER__

typedef __builtin_va_list       va_list;
#define va_start(ap, X)         __builtin_va_start(ap, X)
#define va_arg(ap, type)        __builtin_va_arg(ap, type)
#define va_end(ap)              __builtin_va_end(ap)

#define BUFFER_TEXT ((const char *)0xb8000)

void kputchar(char);

#endif
