/*
 * keyboard.c
 * Copyright (C) 2016 Mehmet Akif TAŞOVA
 * License: GPL Versiom 3 or any later version
 */

#include "idt.h" /* definition of write_port and read_port */

void keyboard_init(void){
	/* 0xFD is 11111101 - enables only IRQ1 (keyboard)*/
	write_port(0x21, 0xFD);
}
