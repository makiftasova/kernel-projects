/*
 * idt.c
 * Copyright (C) 2016 Mehmet Akif TAŞOVA
 * License: GPL Versiom 3 or any later version
 */

#include "idt.h"

#include "keyboard.h" /* for keyboard_handler(void) */

struct IDT_entry IDT[IDT_SIZE];

void idt_init(void){
	unsigned long keyboard_address;
	unsigned long idt_address;
	unsigned long idt_ptr[2];

	/* populate idt entry for keyboard inputs*/
	keyboard_address = (unsigned long)keyboard_handler;
	IDT[0x21].off_lbits = keyboard_address & 0xffff;
	IDT[0x21].selector = IDT_KERNEL_CODE_SEGMENT_OFFSET;
	IDT[0x21].zero = 0;
	IDT[0x21].type_attr = IDT_INTERRUPT_GATE;
	IDT[0x21].off_hbits = (keyboard_address & 0xffff0000) >> 16;

	/*				PORTS
	*			PIC1	PIC2
	* command	0x20	0xA0
	* Data		0x21	0xA1
	*/

	/* ICW1 begin initialization */
	write_port(0x20, 0x11);
	write_port(0xA0, 0x11);

	/* ICW2 - remap offset address of IDT */
	/*
	 * In x86 protected mode, we have to remap the PICs beyond 0x20 because
	 * Intel have designated the first 32 interrupts as "reserved" for cpu exceptions
	 */
	write_port(0x21, 0x20);
	write_port(0xA1, 0x28);

	/* ICW3 setup cascading */
	write_port(0x21 , 0x00);
	write_port(0xA1 , 0x00);

	/* ICW4 - environment info */
	write_port(0x21 , 0x01);
	write_port(0xA1 , 0x01);
	/* Initialization finished */

	/* mask interrupts */
	write_port(0x21 , 0xff);
	write_port(0xA1 , 0xff);

	/* fill IDT descriptor */
	idt_address = (unsigned long) IDT;
	idt_ptr[0] = (sizeof (struct IDT_entry) * IDT_SIZE) + ((idt_address & 0xffff) << 16);
	idt_ptr[1] = idt_address >> 16;

	load_idt(idt_ptr);
}