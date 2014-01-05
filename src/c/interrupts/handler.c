#include "../header.h"

void int_handler(void)
{
	kernelpanic("Interrupt");
}
