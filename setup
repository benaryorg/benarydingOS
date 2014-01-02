#!/bin/sh
test build
if [ $? ];then
	rm -rf build
fi
mkdir build
cd src
for f in $(find *);do
	ls $f/. >/dev/null 2>/dev/null
	if [ $? -ne 2 ];then
		mkdir ../build/$f
	fi
done
cd ..
