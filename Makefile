KERNEL_DIR='src/kernel'
MODULE_DIR='src/modules'

base: setup make

all: setup clean make

make: kernel modules

kernel:
	@make -C$(KERNEL_DIR)

modules:
	@make -C$(MODULE_DIR)

setup:
	@mkdir -p build

clean:
	@make -C$(KERNEL_DIR) clean
	@make -C$(MODULE_DIR) clean

.PHONY: all clean base
