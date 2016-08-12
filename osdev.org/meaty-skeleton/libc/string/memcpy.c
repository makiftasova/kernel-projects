/*
 * memcpy.c
 * Copyright (C) 2016 Mehmet Akif TAŞOVA
 * License: GPL Version 3 or any later version
 */

#include <string.h>

void *memcpy(void *restrict dstptr, const void *restrict srcptr, size_t size) {
    unsigned char *dst = (unsigned char *) dstptr;
    const unsigned char *src = (const unsigned char *) srcptr;
    for (size_t i = 0; i < size; ++i)
        dst[i] = src[i];
    return dstptr;
}