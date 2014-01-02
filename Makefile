SRCS = $(shell find -name '*.[cS]')
OBJS = $(subst ./src,./build,$(addsuffix .o,$(basename $(SRCS))))

CC = cc
LD = ld

ASFLAGS = -m32
CFLAGS = -m32 -Wall -g -fno-stack-protector -nostdinc
LDFLAGS = -melf_i386 -Ttext=0x100000

build/kernel: $(OBJS)
	$(LD) $(LDFLAGS) -o $(shell echo $@ | sed -e 's,src,build,') $(shell echo $^ | sed -e 's,src,build,g')

%.o: %.c
	$(CC) $(CFLAGS) -c -o $(shell echo $@ | sed -e 's,src,build,') $^

%.o: %.S
	$(CC) $(ASFLAGS) -c -o $(shell echo $@ | sed -e 's,src,build,') $^

clean:
	rm $(OBJS)

setup:
	$(shell cp -r src build)
	$(shell cd build)
	$(rm -rf *.c)

.PHONY: clean
