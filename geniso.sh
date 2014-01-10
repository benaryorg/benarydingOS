#!/bin/sh
# geniso.sh -- generate a bootable ISO image with the GRUB bootloader
# (c) 2014 nilsding
# license: beerware
#
# tested in Gentoo GNU/Linux
# you need to emerge sys-boot/grub:0 if you want to want that script to work
# oh and app-cdr/cdrtools! that one is needed for mkisofs

GENISOARGS='-R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -V "BDOS" -o build/benarydingOS.iso build/iso'

GENISOCOMMAND='genisoimage'

command -v genisoimage >/dev/null 2>&1 || {
	command -v mkisofs >/dev/null 2>&1 || {
		echo "mkisofs or genisoimage is required but was not found on your system."
		exit 1
	}
	GENISOCOMMAND='mkisofs'
}

printf "\033[32;1m * \033[0mCreating directories\033[0m\n"
mkdir -p build/iso/boot/grub

printf "\033[32;1m * \033[0mCopying grub stage2\033[0m\n"
cp /lib/grub/i386-pc/stage2_eltorito build/iso/boot/grub/

echo "default 0
timeout 30

title Boot benarydingOS
kernel /boot/kernel

title Boot from hard disk
chainloader (hd0)+1
" > build/iso/boot/grub/menu.lst

printf "\033[32;1m * \033[0mCopying kernel\033[0m\n"
cp build/kernel build/iso/boot/kernel

printf "\033[32;1m * \033[0mStarting mkisofs or genisoimage\033[0m\n"
$GENISOCOMMAND $GENISOARGS

printf "\033[32;1m * \033[0mThe iso is in \033[1mbuild/benarydingOS.iso\033[0m\n"
