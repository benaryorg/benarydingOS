#ifndef __SYSCALLS_HEADER__
#define __SYSCALLS_HEADER__

#define SYSCALL_PUTCHAR				0x00
#define SYSCALL_CLEAR				0x01
#define SYSCALL_TASK_NEXT			0x02
#define SYSCALL_HOOK_INT			0x03
#define SYSCALL_INB					0x04
#define SYSCALL_OUTB				0x05 //TODO
#define SYSCALL_TASK_EXIT			0x06

#define SYSCALL_REBOOT				0xFF //TODO

#endif
