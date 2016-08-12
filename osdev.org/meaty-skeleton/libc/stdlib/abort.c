/*
 * abort.c
 * Copyright (C) 2016 Mehmet Akif TAŞOVA
 * License: GPL Version 3 or any later version
 */

#include <stdio.h>
#include <stdlib.h>

__attribute__((__noreturn__))
void abort(void) {
    /* TODO: Add proper kernel panic */
    printf("Kernel Panic: abort()\n");
    while (1) {}
    __builtin_unreachable();
}