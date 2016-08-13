/*
 * crtn.S
 * Copyright (C) 2016 Mehmet Akif TAŞOVA
 * License: GPL Version 3 or any later version
 */

.section .init
	/* gcc will nicely put the contents of crtend.o's .init section here. */
	pop %esp
	ret

.section .fini
	/* gcc will nicely put the contents of crtend.o's .fini section here. */
	pop %esp
	ret
