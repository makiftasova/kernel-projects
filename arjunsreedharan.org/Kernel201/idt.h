/*
 * idt.h
 * Interrupt Descriptor Table
 * Copyright (C) 2016 Mehmet Akif TAŞOVA
 * License: GPL Version 3 or any later version
 */

#pragma once

#define IDT_SIZE 256
#define IDT_INTERRUPT_GATE 0x8e
#define IDT_KERNEL_CODE_SEGMENT_OFFSET 0x08

struct IDT_entry{
	unsigned short int off_lbits; /* offset lower bits */
	unsigned short int selector;
	unsigned char zero;
	unsigned char type_attr;
	unsigned short int off_hbits; /* offset higher bits */
};


extern char read_port(unsigned short port);
extern void write_port(unsigned short port, unsigned char data);
extern void load_idt(unsigned long *idt_ptr);

/*
 * init idt
 */
extern void idt_init(void);