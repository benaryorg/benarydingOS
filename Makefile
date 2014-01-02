SRCS = $(shell find -name '*.[cS]')
#OBJS = $(subst ./src,./build,$(addsuffix .o,$(basename $(SRCS))))
OBJS = $(addsuffix .o,$(basename $(SRCS)))

CC = cc
LD = ld

ASFLAGS = -m32
CFLAGS = -m32 -Wall -g -fno-stack-protector -nostdinc
LDFLAGS = -melf_i386 -Ttext=0x100000

build/kernel: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(subst src,build,$^)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $(subst src,build,$@) $^

%.o: %.S
	$(CC) $(ASFLAGS) -c -o $(subst src,build,$@) $^

clean:
	rm $(subst ./src,./build,$(OBJS))

.PHONY: clean
