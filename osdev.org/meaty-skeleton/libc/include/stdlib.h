/*
 * stdlib.h
 * Copyright (C) 2016 Mehmet Akif TAŞOVA
 * License: GPL Version 3 or any later version
 */

#ifndef _STDLIB_H
#define _STDLIB_H 
 
#include <sys/cdefs.h>
 
#ifdef __cplusplus
extern "C" {
#endif
 
__attribute__((__noreturn__))
void abort(void);
 
#ifdef __cplusplus
}
#endif
 
#endif