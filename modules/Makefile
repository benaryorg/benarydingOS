SRCS = $(shell find -name '*.c')
OBJS = $(addsuffix .o,$(basename $(SRCS)))

CC = cc
LD = ld

ASFLAGS = -m32
CFLAGS = -m32 -Wall -g -fno-stack-protector -nostdinc -Iheader
LDFLAGS = -melf_i386 -Tlinker/linker.ld

all: $(addprefix ../build/,$(addsuffix .bin,$(basename $(notdir $(OBJS))))) clean

$(addprefix ../build/,$(addsuffix .bin,$(basename $(notdir $(OBJS))))): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm $(OBJS)

.PHONY: clean
