SRCS = $(shell find kernel -name '*.[cS]')
OBJS = $(addsuffix .o,$(basename $(SRCS)))

CC = cc
LD = ld

ASFLAGS = -m32
CFLAGS = -m32 -Wall -g -fno-stack-protector -nostdinc -std=gnu89 -Ikernel/c/header/
LDFLAGS = -melf_i386 -Ttext=0x100000 -T kernel/linker/kernel.ld

all: kernel modules

modules:
	@make -Cmodules

kernel: $(OBJS)
	$(LD) $(LDFLAGS) -o build/kernel $(subst kernel,build/kernel_,$^)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $(subst kernel,build/kernel_,$@) $^

%.o: %.S
	$(CC) $(ASFLAGS) -c -o $(subst kernel,build/kernel_,$@) $^

clean:
	rm -f $(subst ./kernel,./build/kernel_,$(OBJS))

.PHONY: clean
