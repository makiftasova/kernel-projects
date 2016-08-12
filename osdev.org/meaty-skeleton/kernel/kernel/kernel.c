/*
 * kernel.c
 * Copyright (C) 2016 Mehmet Akif TAŞOVA
 * License: GPL Version 3 or any later version
 */

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/tty.h>

void kernel_early(void) {
    terminal_initialize();
}

void kernel_main(void) {
    printf("Welcome to he Tasovix Kernel\n");
}