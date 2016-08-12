/*
 * strlen.c.c
 * Copyright (C) 2016 Mehmet Akif TAŞOVA
 * License: GPL Version 3 or any later version
 */

#include <string.h>

size_t strlen(const char *string) {
    size_t result = 0;
    while (string[result])
        ++result;
    return result;
}