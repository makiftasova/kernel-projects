/*
 * kernel.c
 * Copyright (C) 2016 Mehmet Akif TAŞOVA
 * License: GPL Version 3 or any later version
 */

#include "idt.h"
#include "keyboard.h"
#include "keyboard_map.h"

/*
 * SCREEN SETTINGS
 */
 #define LINES 25
 #define COLUMNS_PER_LINE 80
 #define BYTES_PER_ELEMENT 2
 #define SCREEN_SIZE BYTES_PER_ELEMENT * COLUMNS_PER_LINE * LINES

/* KERNEL_PUTS ATTRIBUTES
 * higher 4 bit -> background color
 * lower 4 bit -> foreground color
 */
#define KPUTS_BLUE_ON_BLACK 0x01
#define KPUTS_RED_ON_BLACK 0x04
#define KPUTS_GREY_ON_BLACK 0x07

/* video variables */
unsigned int vid_curr_loc = 0;
char *vid_ptr = (char *) 0xb8000;


void kputc(const char c, const char attr){
	if(vid_curr_loc >= SCREEN_SIZE)
		vid_curr_loc = 0;

	vid_ptr[vid_curr_loc++] = c;
	vid_ptr[vid_curr_loc++] = attr;
}

void kprint(const char *str)
{
	unsigned int i = 0;
	while (str[i] != '\0') 
		kputc(str[i++], KPUTS_GREY_ON_BLACK);
}

/*
 * prints error message
 */
void kerror(const char *str){
	unsigned int i = 0;
	while(str[i] != '\0')
		kputc(str[i++], KPUTS_RED_ON_BLACK);
}

void kprint_newline(void)
{
	unsigned int line_size = BYTES_PER_ELEMENT * COLUMNS_PER_LINE;
	vid_curr_loc = vid_curr_loc + (line_size - vid_curr_loc % (line_size));
}

/*
 * Clears screen
 * there are 25 lines each of 80 coulmns; each elemnet takes 2 bytes.
 */
void clear_screen(void)
{
	unsigned int i = 0;
	while (i < SCREEN_SIZE) {
		vid_ptr[i++] = ' ';
		vid_ptr[i++] = KPUTS_GREY_ON_BLACK;
	}
}

void keyboard_handler_main(void){
	unsigned char status;
	char keycode;
	char key;

	write_port(0x20, 0x20);

	status = read_port(KEYBOARD_STATUS_PORT);
	/* Lowest bit of status will be set if buffer is not empty */
	if (status & 0x01){
		keycode = read_port(KEYBOARD_DATA_PORT);
		
		if (keycode < 0)
			return;
		if(keycode == KEYBOARD_KEYCODE_ENTER){
			kprint_newline();
			return;
		}
		key = keyboard_map[keycode];
		kputc(key, KPUTS_GREY_ON_BLACK);
	}
}

void kmain(void){
	const char *str = "welcome to the kernel";

	clear_screen();
	kerror(str);
	kprint_newline();
	kprint_newline();

	idt_init();
	keyboard_init();

	while(1)
		;

	return;
}