/*
 * putchar.c
 * Copyright (C) 2016 Mehmet Akif TAŞOVA
 * License: GPL Version 3 or any later version
 */

#include <stdio.h>

#ifdef __is_tasovix_kernel
#include <kernel/tty.h>
#endif

int putchar(int ic) {
#ifdef __is_tasovix_kernel
    char c = (char) ic;
    terminal_write(&c, sizeof(c));
#else
    /* TODO: Implement write syscall */
#endif
     return ic;

}
