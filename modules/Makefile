SRCS = $(shell find -name '*.c')
OBJS = $(addsuffix .o,$(basename $(SRCS)))

CC = gcc
LD = ld

ASFLAGS = -m32
CFLAGS = -m32 -Wall -g -fno-stack-protector -nostdinc -I include
LDFLAGS = -melf_i386 -Tlinker.ld

$(addprefix ../build/,$(addsuffix .bin,$(basename $(notdir $(OBJS))))): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^
	@clean

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm $(OBJS)

.PHONY: clean
