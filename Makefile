base: setup make

all: setup clean make

make:
	@make -Ckernel
	@make -Cmodules

setup:
	@mkdir -p build

clean:
	@make -Ckernel clean
	@make -Cmodules clean

.PHONY: all clean base
