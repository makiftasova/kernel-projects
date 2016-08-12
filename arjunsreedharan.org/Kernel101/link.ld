/*
 * link.ld
 * Copyright (C) 2016 Mehmet Akif TAŞOVA
 * License: GPL Version 3 or any later version
 */

 OUTPUT_FORMAT(elf32-i386)
 ENTRY(start)
 SECTIONS
 	{
 	. = 0x100000;
 	.text : { *(.text) }
 	.data : { *(.data) }
 	.bss  : { *(.bss) }
 	}