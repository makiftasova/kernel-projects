/*
 * memset.c
 * Copyright (C) 2016 Mehmet Akif TAŞOVA
 * License: GPL Version 3 or any later version
 */

#include <string.h>

void *memset(void *bufptr, int value, size_t size) {
    unsigned char *buf = (unsigned char *) bufptr;
    for (size_t i = 0; i < size; ++i)
        buf[i] = (unsigned char) value;
    return bufptr;
}