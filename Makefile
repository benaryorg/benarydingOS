CC = cc
LD = ld

ASFLAGS = -m32
CFLAGS = -m32 -Wall -g -fno-stack-protector -nostdinc -std=gnu89
LDFLAGS = -melf_i386 -Ttext=0x100000 -T src/linker/kernel.ld

dist/kernel: build/kernel build/modules
	@echo OS

build/modules:
	@echo modules

build/kernel:
	@echo kernel

.PHONY: clean
