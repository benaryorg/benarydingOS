#ifndef __INTERRUPT_HANDLER_HEADER__
#define __INTERRUPT_HANDLER_HEADER__

void int_handler(void)
{
	printf("Interrupt!");
	while(1);
}

#endif
