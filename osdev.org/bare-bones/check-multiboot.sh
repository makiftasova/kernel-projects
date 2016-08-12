#!/usr/bin/env bash
if grub2-file --is-x86-multiboot kernel.bin; then
  echo multiboot confirmed
else
  echo the file is not multiboot
fi