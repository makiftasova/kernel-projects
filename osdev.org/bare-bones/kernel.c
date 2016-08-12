/*
 * kernel.c
 * Copyright (C) 2016 Mehmet Akif TAŞOVA
 * License: GPL Version 3 or any later version
 */

 #include <stdbool.h>
 #include <stddef.h>
 #include <stdint.h>

 #ifndef __i386__
 #error "This kernel needs to be compiled with a ix86-elf compiler"
 #endif

 /* Hardware text mode color constants */
 enum vga_color {
	COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GREY = 7,
	COLOR_DARK_GREY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_LIGHT_MAGENTA = 13,
	COLOR_LIGHT_BROWN = 14,
	COLOR_WHITE = 15,
};

uint8_t make_color(enum vga_color fg, enum vga_color bg){
	return fg | bg << 4;
}

uint16_t make_vgaentry(const char c, const uint8_t color){
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}

size_t strlen(const char *str){
	size_t len = 0;
	while(str[len])
		++len;
	return len;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_initialize(void){
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(const uint8_t color){
	terminal_color = color;
}

void terminal_putentryat(const char c, const uint8_t color, const size_t x, const size_t y){
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = make_vgaentry(c, color);
}

void terminal_newline(void){
	if(terminal_row + 1 == VGA_HEIGHT){
		for(size_t y = 1; y < VGA_HEIGHT; ++y){
			for(size_t x = 0; x < VGA_WIDTH; ++x){
				size_t old = (y - 1) * VGA_WIDTH + x;
				size_t new = y* VGA_WIDTH + x;
				terminal_buffer[old] = terminal_buffer[new];
			}
		}
		for(size_t x = 0; x < VGA_WIDTH; ++x){
			size_t index = (VGA_HEIGHT - 1) * VGA_WIDTH + x;
			terminal_buffer[index] = ' '; 
		}
	}
	else
		++terminal_row;
		
	terminal_column = 0;
}

void terminal_putchar(const char c) {
	if(c == '\n'){
		terminal_newline();
		return;
	}

	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT) {
			terminal_row = 0;
		}
	}
}

void terminal_puts(const char* str) {
	size_t len = strlen(str);
	for (size_t i = 0; i < len; i++)
		terminal_putchar(str[i]);
}

/* kernel_main */
void kernel_main(void){
	terminal_initialize();

	terminal_puts("Hello Kernel World!\n");
	for(char i = 'a'; i < 'z'; ++i ){
		terminal_putchar(i);
		terminal_newline();
	}
	
}
