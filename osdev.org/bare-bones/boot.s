/*
 * boot.s
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

 # Setup stack
 .section .bss
 .align 16
 stack_bottom:
 .skip 16384 # 16KB of initial stack
 stack_top:


.section .text
.global _start
.extern kernel_main

.type _start, @function

_start:
	mov $stack_top, %esp	# set esp register to initialize stack
	call kernel_main		# call high-level kernel
							# let's put cpu into infinite loop
	cli 					# disable interrupts
1:	hlt						# wait for any interrupt to happen
	jmp 1b 					# jump to hlt if any non maskable interrupt happens

.size _start, . - _start	# set the size of start interrupt
