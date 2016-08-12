/*
 * kernel.c
 * Copyright (C) 2016 Mehmet Akif TAŞOVA
 * License: GPL Version 3 or any later version
 */

 /* KERNEL_PUTS ATTRIBUTES
  * msb 4 bit -> background color
  * lsb 4 bit -> foreground color
  */
#define KPUTS_BLUE_ON_BLACK 0x01
#define KPUTS_RED_ON_BLACK 0x04
#define KPUTS_GREY_ON_BLACK 0x07

/*
 * Clears screen
 * there are 25 lines each of 80 coulmns; each elemnet takes 2 bytes.
 */
 void kernel_clear_screen(char *vidptr){
 	for( unsigned int i = 0; i < 80 * 25 * 2; i += 2){
 		/* set character to blank*/
 		vidptr[i] = ' ';
 		/* set attribute byte*/
 		vidptr[i+1] = KPUTS_GREY_ON_BLACK; /* light grey on black screen */
 	}
 }

 void kernel_puts(char *vidptr, const char *str, const char attr){
 	static unsigned int curr_index = 0; /* cursor position */
 	unsigned int i = 0;
 	
 	while(str[i] != '\0'){
 		vidptr[curr_index] = str[i]; /* character's ascii */
 		vidptr[curr_index + 1] = attr; /* attribute-byte */
 		++i;
 		curr_index += 2;
 	}

 	if(curr_index >= 80 * 25 * 2)
 		curr_index = 0;

 }

 void kmain(void){
 	const char *str = "welcome to the kernel";
 	char *vidptr = (char *) 0xb8000; /* video memory start*/
 	unsigned int i = 0;

 	kernel_clear_screen(vidptr);

 	kernel_puts(vidptr, str, KPUTS_GREY_ON_BLACK);
 	kernel_puts(vidptr, str, KPUTS_RED_ON_BLACK);

 	return;
 }