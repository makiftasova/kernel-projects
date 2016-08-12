#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/tasovix.kernel isodir/boot/tasovix.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "tasovix" {
	multiboot /boot/tasovix.kernel
}
EOF
grub2-mkrescue -o tasovix.iso isodir
