/*
 * tty.h
 * Copyright (C) 2016 Mehmet Akif TAŞOVA
 * License: GPL Version 3 or any later version
 */
 
#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H
 
#include <stddef.h>
 
void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);
 
#endif