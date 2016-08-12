/*
 * puts.c
 * Copyright (C) 2016 Mehmet Akif TAŞOVA
 * License: GPL Version 3 or any later version
 */

#include <stdio.h>

int puts(const char *string) {
    return printf("%s\n", string);
}
