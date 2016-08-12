/*
 * boot.S
 * Copyright (C) 2016 Mehmet Akif TAŞOVA
 * License: GPL Version 3 or any later version
 */

# Multiboot header constants
.set ALIGN,	1<<0
.set MEMINFO,	1<<1
.set FLAGS,	ALIGN | MEMINFO
.set MAGIC,	0x1BADB002
.set CHECKSUM,	-(MAGIC + FLAGS)

# Declare multiboot header
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Reserve stack for initial thread
.section .bootstrap_stack, "aw", @nobits
stack_bottom:
.skip 16384 # 16KB of initial stack
stack_top:

# Kernel entry point
.section .text
.global _start

.extern kernel_early
.extern _init
.extern kernel_main

.type _start, @function

_start:
		movl $stack_top, %esp

		call kernel_early		# initialize core kernel

		call _init				# call global constructors

		call kernel_main		# call main kernel

								# let's put cpu into infinite loop
		cli 					# disable interrupts
.Lhang:	hlt						# wait for any interrupt to happen
		jmp .Lhang 				# jump to hlt if any non maskable interrupt happens

.size _start, . - _start		# set the size of start interrupt
