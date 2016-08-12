#!/usr/bin/env bash
as --32 boot.s -o boot.o # build in 32 bit mode
gcc -m32 -c kernel.c -o kernel.o -O2 -ffreestanding -nostdlib -Wall -Wextra
ld -m elf_i386 -T linker.ld boot.o kernel.o -o kernel.bin