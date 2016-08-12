/*
 * keyboard.h
 * Copyright (C) 2016 Mehmet Akif TAŞOVA
 * License: GPL Version 3 or any later version
 */
#pragma once


#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

#define KEYBOARD_KEYCODE_ENTER 0x1C

extern void keyboard_handler(void);

extern void keyboard_init(void);