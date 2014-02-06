SRCS = $(shell find -maxdepth 1 -name '*.c')
OBJS = $(addsuffix .o,$(basename $(SRCS)))
LIBSRCS = $(shell find libs -name '*.c')
LIBOBJS = $(addsuffix .o,$(basename $(LIBSRCS)))

CC = cc
LD = ld

ASFLAGS = -m32
CFLAGS = -m32 -Wall -g -fno-stack-protector -nostdinc -Iheader -ffunction-sections
LDFLAGS = -melf_i386 -Tlinker/linker.ld

all: cleanmodules $(addprefix ../build/,$(addsuffix .bin,$(basename $(notdir $(OBJS))))) clean

$(addprefix ../build/,$(addsuffix .bin,$(basename $(notdir $(OBJS))))): $(LIBOBJS) $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -f $(OBJS)

cleanall: clean cleanmodules
	rm -f $(LIBOBJS)

cleanmodules:
	rm -f ../build/*.bin

.PHONY: clean cleanall cleanmodules
