;; kernel.asm
;; author: Mehmet kif TAŞOVA
;; makiftasova@gmail.com


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
extern kmain					; defined in kernel.c file

start:
	cli 						; block interrupts
	mov esp, stack_space		; set stack pointer
	call kmain					; call kernel's main
	hlt 						; Halt the CPU

section .bss
resb 8192						; allocate 8KB for stack

stack_space:
