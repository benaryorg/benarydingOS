benarydingOS
============

An Operating System by benaryorg and nilsding

How to build
------------

Building our OS easy!

    $ ./setup.sh
    $ make

If you want to build a bootable ISO, run this:

    $ ./geniso.sh

You need mkisofs and GRUB Legacy for it to work.  Gentoo users simply `emerge app-cdr/cdrtools sys-boot/grub:0`.
The iso is located in `build/benarydingOS.iso`.

Licensing
---------

25% of our code is from lowlevel.eu (THANKS!) thats why this OS is under the "CC BY-NC-SA 3.0 DE"
http://creativecommons.org/licenses/by-nc-sa/3.0/de/legalcode

Human readable:
http://creativecommons.org/licenses/by-nc-sa/3.0/de/
