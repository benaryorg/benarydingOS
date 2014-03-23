#ifndef __INTERRUPT_HANDLER_HEADER__
#define __INTERRUPT_HANDLER_HEADER__

#define TASKS_SIZE 128

#include "header.h"

typedef struct
{
	cpu_state_t *cpu;
    page_context_t *context;
//	uint8_t ticks;
//	uint8_t tick;
}
task_t;

cpu_state_t *int_handler(cpu_state_t *);
cpu_state_t *handler_exception(cpu_state_t *);
cpu_state_t *handler_hardware_int(cpu_state_t *);
cpu_state_t *handler_syscall(cpu_state_t *);

cpu_state_t *(**interrupt_handlers(int))(cpu_state_t *);
cpu_state_t *(*getinterrupthandler(int))(cpu_state_t *);
void setinterrupthandler(int,cpu_state_t *(*)(cpu_state_t *));

cpu_state_t *(**syscall_handlers(int))(cpu_state_t *);
cpu_state_t *(*getsyscallhandler(int))(cpu_state_t *);
void setsyscallhandler(int,cpu_state_t *(*)(cpu_state_t *));

task_t *task_func(int);
task_t *get_task_by_cpu(cpu_state_t *);
task_t *task_schedule(task_t *);
task_t *task_next(void);
void exit(int);
cpu_state_t *cpu_new(void *,char);

#endif
