#!/bin/sh

QEMU_ARGS="-kernel build/kernel $@"

command -v qemu >/dev/null 2>&1 || {
    echo "qemu is required but was not found on your system."
    exit 1
}

qemu $QEMU_ARGS || qemu-system-i386 $QEMU_ARGS
