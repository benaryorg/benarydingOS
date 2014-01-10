# benarydingOS

An Operating System by benaryorg and nilsding

## How to build

Seting up the environment:

    $ ./setup.sh

Building our OS easy!

    $ make

If you want to build a bootable ISO, run this:

    $ ./geniso.sh

You need mkisofs and GRUB Legacy for it to work.  Gentoo users simply `emerge app-cdr/cdrtools sys-boot/grub:0`.
The iso is located in `build/benarydingOS.iso`.

## How to run

### QEMU

Simply run the qemu start script:

    $ ./qemu.sh

If you built the bootable ISO, you also may want to invoke QEMU manually:

    $ qemu -cdrom build/benarydingOS.iso

### Bochs

After building the ISO, you can run our OS in Bochs using the following command:

    $ bochs -q 'boot:cdrom' 'ata0-master: type=cdrom, path=build/benarydingOS.iso, status=inserted'

### Real hardware

There are two ways to run our OS on real hardware:

#### GRUB Legacy (0.xx)
Add the following three lines to your `/boot/grub/menu.lst`:

    title benarydingOS
    root (hd0,0)
    kernel /boot/kernel

#### Burn the ISO
You can burn the built ISO to a CD, if you _really_ feel like wasting one.  Currently **NOT** supported!

## Licensing

Some essential parts of our code are very similar to the code on lowlevel.eu and mostly based on it!

Their code is under the "CC BY-NC-SA 3.0 DE" so our code is under this licence too.
http://creativecommons.org/licenses/by-nc-sa/3.0/de/legalcode

Human readable:
http://creativecommons.org/licenses/by-nc-sa/3.0/de/
