#ifndef __UTILS_HEADER__
#define __UTILS_HEADER__

static const char digits[] = "0123456789ABCDEF";

/* I/O */
inline void outb(uint16_t,uint8_t);
inline unsigned char inb(uint16_t);

/* benaryorglib */
void haltcpu(void);
void kernelpanic(const char *);
void register_reload(void);

/* memoryfunctions */
void *memcpy(void *,const void *,unsigned int);
void *memset(void *,int,unsigned int);

/* stdlib */
int atoi (const char *nptr);

/* math */
int _pow(int a, int b);

/* nonstandard extensions, fuck yeah! */
const char *itoa (int value, char *str, int base);
const char *uitoa (unsigned int value, char *str, int base);

#endif
