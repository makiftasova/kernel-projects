/*
 * crti.S
 * Copyright (C) 2016 Mehmet Akif TAŞOVA
 * License: GPL Version 3 or any later version
 */

.section .init
.global _init
.type _init, @function
_init:
	push %esp
	movl %esp, %ebp
	/* gcc will nicely put the contents of crtbegin.o's .init section here. */

.section .fini
.global _fini
.type _fini, @function
_fini:
	push %esp
	movl %esp, %ebp
	/* gcc will nicely put the contents of crtbegin.o's .fini section here. */
