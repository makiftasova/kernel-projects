/*
 * tty.c
 * Copyright (C) 2016 Mehmet Akif TAŞOVA
 * License: GPL Version 3 or any later version
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/vga.h>

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t *terminal_buffer;

void terminal_initialize(void) {
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
    terminal_buffer = (uint16_t *) 0xB8000;
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = make_vgaentry(' ', terminal_color);
        }
    }
}

void terminal_setcolor(const uint8_t color) {
    terminal_color = color;
}

void terminal_putentryat(const char c, const uint8_t color, const size_t x, const size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = make_vgaentry(c, color);
}

void terminal_newline(void) {
    if (terminal_row + 1 == VGA_HEIGHT) {
        for (size_t y = 1; y < VGA_HEIGHT; ++y) {
            for (size_t x = 0; x < VGA_WIDTH; ++x) {
                size_t old = (y - 1) * VGA_WIDTH + x;
                size_t new = y * VGA_WIDTH + x;
                terminal_buffer[old] = terminal_buffer[new];
            }
        }
        for (size_t x = 0; x < VGA_WIDTH; ++x) {
            size_t index = (VGA_HEIGHT - 1) * VGA_WIDTH + x;
            terminal_buffer[index] = ' ';
        }
    } else
        ++terminal_row;

    terminal_column = 0;
}

void terminal_putchar(const char c) {
    if (c == '\n') {
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

void terminal_write(const char *data, size_t size) {
    for (size_t i = 0; i < size; ++i)
        terminal_putchar(data[i]);

}

void terminal_puts(const char *str) {
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++)
        terminal_putchar(str[i]);
}