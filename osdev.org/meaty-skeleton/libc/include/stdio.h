/*
 * stdio.h
 * Copyright (C) 2016 Mehmet Akif TAŞOVA
 * License: GPL Version 3 or any later version
 */

#ifndef _STDIO_H
#define _STDIO_H 1
 
#include <sys/cdefs.h>
 
#ifdef __cplusplus
extern "C" {
#endif
 
int printf(const char* __restrict, ...);
int putchar(int);
int puts(const char*);
 
#ifdef __cplusplus
}
#endif
 
#endif