.section multiboot
#define MB_MAGIC 0x1badb002
#define MB_FLAGS 0x0
#define MB_CHECKSUM -(MB_MAGIC + MB_FLAGS)

.align 4
.int    MB_MAGIC
.int    MB_FLAGS
.int    MB_CHECKSUM

.section .text

/*#define MB_MAGIC 0x1badb002
#define MB_FLAGS 0x0
#define MB_CHECKSUM -(MB_MAGIC + MB_FLAGS)

.align 4
.int    MB_MAGIC
.int    MB_FLAGS
.int    MB_CHECKSUM*/


.extern init
.extern int_handler

.global _start
_start:
	mov $kstack, %esp
	push %ebx
	call init

_halt:
	cli
	hlt
	jmp _halt

.macro intr_stub nr
.global intr_stub_\nr
intr_stub_\nr:
    pushl $0
	pushl $\nr
	jmp intr_common_handler
.endm
			 
.macro intr_stub_error_code nr
.global intr_stub_\nr
	intr_stub_\nr:
	pushl $\nr
	jmp intr_common_handler
.endm

intr_stub 0
intr_stub 1
intr_stub 2
intr_stub 3
intr_stub 4
intr_stub 5
intr_stub 6
intr_stub 7
intr_stub_error_code 8
intr_stub 9
intr_stub_error_code 10
intr_stub_error_code 11
intr_stub_error_code 12
intr_stub_error_code 13
intr_stub_error_code 14
intr_stub 15
intr_stub 16
intr_stub_error_code 17
intr_stub 18


intr_stub 32
intr_stub 33
intr_stub 34
intr_stub 35
intr_stub 36
intr_stub 37
intr_stub 38
intr_stub 39
intr_stub 40
intr_stub 41
intr_stub 42
intr_stub 43
intr_stub 44
intr_stub 45
intr_stub 46
intr_stub 47

intr_stub 48

.extern int_handler
intr_common_handler:
    // CPU-Zustand sichern
    push %ebp
    push %edi
    push %esi
    push %edx
    push %ecx
    push %ebx
    push %eax
 
    // Handler aufrufen
    push %esp
    call int_handler
    mov %eax,%esp
//    add $4, %esp
 
    // CPU-Zustand wiederherstellen
    pop %eax
    pop %ebx
    pop %ecx
    pop %edx
    pop %esi
    pop %edi
    pop %ebp
 
    // Fehlercode und Interruptnummer vom Stack nehmen
    add $8, %esp
 
    // Ruecksprung zum unterbrochenen Code
    iret

.section .bss
.space 16384
kstack:
