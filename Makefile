SRCS = $(shell find kernel -name '*.[cS]')
OBJS = $(addsuffix .o,$(basename $(SRCS)))

CC = cc
LD = ld

ASFLAGS = -m32
CFLAGS = -m32 -Wall -g -fno-stack-protector -nostdinc -std=gnu89
LDFLAGS = -melf_i386 -Ttext=0x100000 -T kernel/linker/kernel.ld

all: build/kernel
	make -Cmodules

build/kernel: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(subst kernel,build/kernel_,$^)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $(subst kernel,build/kernel_,$@) $^

%.o: %.S
	$(CC) $(ASFLAGS) -c -o $(subst kernel,build/kernel_,$@) $^


clean:
	rm $(subst ./kernel,./build/kernel_,$(OBJS))

.PHONY: clean
