BUILD_DIR=../../build

SRCS = $(shell find -maxdepth 1 -name '*.c')
OBJS = $(addsuffix .o,$(basename $(SRCS)))
MODS = $(addprefix $(BUILD_DIR)/,$(notdir $(addsuffix .bin,$(basename $(OBJS)))))
LIBSRCS = $(shell find libs -name '*.c')
LIBOBJS = $(addsuffix .o,$(basename $(LIBSRCS)))

CC = cc
LD = ld

ASFLAGS = -m32
CFLAGS = -m32 -Wall -g -fno-stack-protector -nostdinc -Iheader -ffunction-sections
LDFLAGS = -melf_i386 -Tlinker.ld

default: $(MODS)

all: $(MODS) clean

%.bin: $(LIBOBJS) $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(LIBOBJS) $(addsuffix .o,$(basename $(notdir $@)))

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	@rm -f $(OBJS)
	@rm -f $(LIBOBJS)
	@rm -f $(BUILD_DIR)/*.bin

.PHONY: clean
