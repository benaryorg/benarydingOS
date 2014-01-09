#!/bin/sh
test build
if [ $? ];then
	rm -rf build
fi
mkdir build
mkdir build/kernel_
mkdir build/modules_
cd kernel
for f in $(find *);do
	ls $f/. >/dev/null 2>/dev/null
	if [ $? -ne 2 ];then
		mkdir ../build/kernel_/$f
	fi
done
cd ..
