SRCS = $(shell find -name '*.[cS]')
#OBJS = $(subst ./src,./build,$(addsuffix .o,$(basename $(SRCS))))
OBJS = $(addsuffix .o,$(basename $(SRCS)))

CC = cc
LD = ld

ASFLAGS = -m32
CFLAGS = -m32 -Wall -g -fno-stack-protector -nostdinc -std=gnu89
LDFLAGS = -melf_i386 -Ttext=0x100000 -T src/linker/kernel.ld

../build/kernel: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(subst src,../build,$^)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $(subst src,../build,$@) $^

%.o: %.S
	$(CC) $(ASFLAGS) -c -o $(subst src,../build,$@) $^

setup:
	$(shell ./setup.sh)

clean:
	rm $(subst ./src,./build,$(OBJS))

.PHONY: clean
