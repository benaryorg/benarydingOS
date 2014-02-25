all: build/kernel
	@make -Ckernel
	@make -Cmodules
