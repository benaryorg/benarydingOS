all: setup
	@make -Ckernel
	@make -Cmodules

setup:
	@mkdir -p build

.PHONY: all setup