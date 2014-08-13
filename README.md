# benarydingOS

An Operating System by benaryorg and nilsding

Warning! Abandoned at the moment!
Me (benaryorg) will start a complete rewrite soon.

## How to build

Building our OS easy!  First, you set up the build environment and then you just run `make`.

    $ ./setup.sh
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
You can burn the built ISO to a CD, if you _really_ feel like wasting one.  Currently supported (see Bug #11)!

## Support

Somthing not working?  Have questions?  Want to help?

### Github

Feel free to submit issues!  Please, we need them!
You can also send pull requests if you already fixed something!

### E-Mail

benaryorg: binary@benary.org

### Twitter

benaryorg: @benaryorg

## Licensing

This project is under the license found in the LICENSE file!

Some essential parts of our code are very similar to the code on lowlevel.eu and mostly based on it!

Also they provide a huge Wiki where we got most of our knowledge about Operating Systems from.

Therefore a big "Thanks" and, as we say in German, "Tausend Dank euch allen!"

## Authors

The main authors are:

benaryorg, nilsding and all other contributors!

If you want to have _your_ code explicitly mentioned as such, please add a comment!

We *trust* you!

