#!/usr/bin/env bash
nasm -f elf32 kernel.asm -o kasm.o
gcc -m32 -c kernel.c -o kernel.o
gcc -m32 -c idt.c -o idt.o
gcc -m32 -c keyboard.c -o keyboard.o
ld -m elf_i386 -T link.ld -o kernel.bin kasm.o kernel.o keyboard.o idt.o