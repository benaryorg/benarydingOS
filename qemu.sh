#!/bin/sh

QEMU_ARGS="-kernel build/kernel $@"

qemu $QEMU_ARGS || qemu-system-i386 $QEMU_ARGS
