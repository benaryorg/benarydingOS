#!/bin/sh
# geniso.sh -- generate a bootable ISO image with the GRUB bootloader
# (c) 2014 nilsding
# license: beerware
#
# tested in Gentoo GNU/Linux
# you need to emerge sys-boot/grub:0 if you want to want that script to work
# oh and app-cdr/cdrtools! that one is needed for mkisofs

GENISOARGS='-R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -V "BDOS" -o benarydingOS.iso iso'

mkdir -p iso/boot/grub
cp /lib/grub/i386-pc/stage2_eltorito iso/boot/grub/
echo "default 0
timeout 30

title Boot benarydingOS
kernel /boot/kernel

title Boot from hard disk
chainloader (hd0)+1
" > iso/boot/grub/menu.lst
cp build/kernel iso/boot/kernel
genisoimage $GENISOARGS || mkisofs $GENISOARGS
