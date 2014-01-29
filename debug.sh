#!/bin/sh
# debug.sh -- starts QEMU and prints some extra steps on how to debug the kernel
# (c) 2014 nilsding
# license: beerware

BUILDDIR=build
KERNEL=$BUILDDIR/kernel
QEMU_ARGS="-s -S -kernel $KERNEL -initrd build/*.bin $@"

if command -v qemu >/dev/null 2>&1 ; then
	qemu='qemu'
elif command -v qemu-system-i386 >/dev/null 2>&1 ; then
	qemu='qemu-system-i386'
elif command -v qemu-system-x86_64 >/dev/null 2>&1 ; then
	qemu='qemu-system-x86_64'
else
	echo "qemu is required but was not found on your system."
	exit 1
fi

printf "\033[32;1m * \033[0mStarting QEMU ...\n"
printf "\033[32;1m * \033[0mOpen another terminal, start gdb and type the following:\n"
printf "\033[32;1m * \033[0m  (gdb)\033[1m target remote localhost:1234\033[0m\n"
printf "\033[32;1m * \033[0m  (gdb)\033[1m symbol-file $KERNEL\033[0m\n\n"

printf "\033[33;1m * \033[0mUsage:\n"
printf "\033[33;1m * \033[0m Set a breakpoint in file src/c/init.c on line 5:\n"
printf "\033[33;1m * \033[0m  (gdb)\033[1m break src/c/init.c:5\033[0m\n"
printf "\033[33;1m * \033[0m Run the code until the breakpoint:\n"
printf "\033[33;1m * \033[0m  (gdb)\033[1m continue\033[0m\n"
printf "\033[33;1m * \033[0m Step into:\n"
printf "\033[33;1m * \033[0m  (gdb)\033[1m step\033[0m\n"
printf "\033[33;1m * \033[0m Examine the contents of a variable:\n"
printf "\033[33;1m * \033[0m  (gdb)\033[1m print i\033[0m\n\n"

$qemu $QEMU_ARGS
