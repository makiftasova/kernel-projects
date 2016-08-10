;; kernel.asm
;; Copyright (C) 2016 Mehmet Akif TAŞOVA
;; License: GPL Versiom 3 or any later version


;; NASM directives
bits 32

;; ASM
section .text
	; multiboot spec
	align 4
	dd 0x1BADB002				; magic
	dd 0x00						; flags
	dd - (0x1BADB002 + 0x00)	; checksum

global start
global read_port
global write_port
global load_idt
global keyboard_handler

extern kmain					; defined in kernel.c file
extern keyboard_handler_main	

read_port:
	mov edx, [esp + 4]			
								; al is the lower 8 bits of eax
	in al, dx					; dx is the lower 16 bits of edx
	ret	

write_port:
	mov edx, [esp + 4]
	mov al, [esp +4 + 4]
	out dx, al
	ret

load_idt:
	mov edx, [esp + 4]
	lidt [edx]
	sti 						; turn on interrupts
	ret

keyboard_handler:
	call keyboard_handler_main
	iretd

start:
	cli 						; block interrupts
	mov esp, stack_space		; set stack pointer
	call kmain					; call kernel's main
	hlt 						; Halt the CPU

section .bss
resb 8192						; allocate 8KB for stack

stack_space:
