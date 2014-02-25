SRCS = $(shell find . -name '*.[cS]')
OBJS = $(addsuffix .o,$(basename $(SRCS)))

CC = cc
LD = ld

ASFLAGS = -m32
CFLAGS = -m32 -Wall -g -fno-stack-protector -nostdinc -std=gnu89 -Ic/header/
LDFLAGS = -melf_i386 -Ttext=0x100000 -Tlinker/kernel.ld

all: ../build/kernel clean

../build/kernel: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

%.o: %.S
	$(CC) $(ASFLAGS) -c -o $@ $^

clean:
	@rm -f $(OBJS)

.PHONY: clean
