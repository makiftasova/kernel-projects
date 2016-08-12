/*
 * linker.ld
 * Copyright (C) 2016 Mehmet Akif TAŞOVA
 * License: GPL Version 3 or any later version
 */

/* set uoutput format */
OUTPUT_FORMAT(elf32-i386)

/* set start symbol */
ENTRY(_start)

/* set object file sections */
SECTIONS
{
	/* leave some empty space for bootlaoder to put kernel */
	. = 1M; 

	/* put multiboot header */
	.text BLOCK(4K): ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}

	/* read-only data */
	.rodata BLOCK(4K): ALIGN(4K)
	{
		*(.rodata)
	}

	/* read-write data (initialized) */
	.data BLOCK(4K): ALIGN(4K)
	{
		*(.data)
	}

	/* read-write data (uninitialized) */
	.bss BLOCK(4K): ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}
}