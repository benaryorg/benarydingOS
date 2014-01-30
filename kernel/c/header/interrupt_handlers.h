#ifndef __INTERRUPT_HANDLER_HEADER__
#define __INTERRUPT_HANDLER_HEADER__

#define TASKS_SIZE 128

#include "header.h"

typedef struct
{
	cpu_state_t *cpu;
	uint8_t ticks;
	uint8_t tick;
}
task_t;

cpu_state_t *int_handler(cpu_state_t *);
cpu_state_t *handler_exception(cpu_state_t *);
cpu_state_t *handler_hardware_int(cpu_state_t *);
cpu_state_t *handler_syscall(cpu_state_t *);

cpu_state_t *(**interrupt_handlers(int))(cpu_state_t *);
cpu_state_t *(*getinterrupthandler(int))(cpu_state_t *);
void setinterrupthandler(int,cpu_state_t *(*)(cpu_state_t *));
cpu_state_t *get_new_cpu(void);
cpu_state_t *task_schedule(cpu_state_t *,char);
cpu_state_t *task_next(cpu_state_t *);
void task_new(void *,char);

#endif
