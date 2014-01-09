#!/bin/sh

QEMU_ARGS="-kernel build/kernel $@"

err=0
qemu=''

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

$qemu $QEMU_ARGS $QEMU_ARGS
