

section .data
	message db "Hello World", 0x0A ; String to print in output

section .text
	global _start	; Entry point for the linker

_start:
	; system call to write to the stdout
	mov eax, 4	; sys_write system call number (0x04)
	mov ebx, 1	; file descriptor 1, stdout
	mov ecx, message ; message to be printed
	mov edx, 13 	; number of bytes to write 
	int 0x80	; interrupt to invoke the system call

	mov eax, 1	; sys_exit to exit the program, sys call number (0x01)
	xor ebx, ebx	; exit status 0
	int 0x80	; interrupt to invoke the system call

; nasm -f elf32 program.asm -o program.o
; linker: ld -m elf_i356 program.o -o program
