BUILD_DIR=../../build

SRCS = $(shell find . -name '*.[cS]')
OBJS = $(addsuffix .o,$(basename $(SRCS)))

CC = cc
LD = ld

ASFLAGS = -m32
CFLAGS = -m32 -Wall -g -fno-stack-protector -nostdinc -std=gnu89 -Iheader
LDFLAGS = -melf_i386 -Ttext=0x100000 -Tlinker.ld

default: $(BUILD_DIR)/kernel

all: clean $(BUILD_DIR)/kernel

$(BUILD_DIR)/kernel: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

%.o: %.S
	$(CC) $(ASFLAGS) -c -o $@ $^

clean:
	@rm -f $(OBJS)

.PHONY: clean all
