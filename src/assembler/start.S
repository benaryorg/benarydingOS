.section multiboot
#define MB_MAGIC 0x1badb002
#define MB_FLAGS 0x0
#define MB_CHECKSUM -(MB_MAGIC + MB_FLAGS)

.align 4
.int    MB_MAGIC
.int    MB_FLAGS
.int    MB_CHECKSUM

.section .text
.extern main

.global _start
_start:
	mov $kstack, %esp
	call main

_halt:
	cli
	hlt
	jmp _halt

.section .bss
.space 16384
kstack:
