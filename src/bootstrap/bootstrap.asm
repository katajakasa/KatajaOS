[BITS 32]
ALIGN 8

[SECTION .header]

mb_header_start:
    ; Header
	DD	0xE85250D6
	DD	0
	DD	mb_header_end - mb_header_start
	DD	-(0xE85250D6 + (mb_header_end - mb_header_start))
    
	DW	0, 0
	DD	8
mb_header_end:

[SECTION .boot]
[GLOBAL bootstrap]
[EXTERN pos_stack]
[EXTERN pos_pml4]
[EXTERN pos_pdpt]
[EXTERN pos_pd]

bootstrap:
    ; Save multiboot header to edx
    mov edx, eax

    ; Load new GDT
    mov eax, gdt_r1
	lgdt [eax]

    ; Set stack
    mov esp, pos_stack
    
    ; Page tables
	mov eax, pos_pdpt
	or eax, 1
	mov [pos_pml4], eax
	mov [pos_pml4 + 0xFF8], eax
 
	mov eax, pos_pd
	or eax, 1
	mov [pos_pdpt], eax
	mov [pos_pdpt + 0xFF0], eax
 
	mov dword [pos_pd], 0x000083
	mov dword [pos_pd + 8], 0x200083
	mov dword [pos_pd + 16], 0x400083
	mov dword [pos_pd + 24], 0x600083
    
	; Load CR3 with PML4
	mov eax, pos_pml4
	mov cr3, eax
    
	; PAE on
	mov eax, cr4
	or eax, 1 << 5
	mov cr4, eax
 
	; Long Mode on
	mov ecx, 0xC0000080
	rdmsr
	or eax, 1 << 8
	wrmsr
 
	; Paging on
	mov eax, cr0
	or eax, 1 << 31
	mov cr0, eax
    
    ; Load new GDT
	mov eax, gdt_r2
	lgdt [eax]
    
	push 0x08
	push .longmode_realm
	retf
    
[BITS 64]
[EXTERN kmain]

.longmode_realm:
    ; Set stack, refresh registers
	mov eax, 0x10
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov rsp, pos_stack + 0xFFFFFFFF80000000
 
	; Long mode GDT
	mov rax, gdt_r3
	lgdt [rax]
    
    ; Call kernel main function. If main returns, kill interrupts and halt.
	mov rax, kmain
    push rdx ; Multiboot2 header
    push rbx ; Multiboot2 info
	call rax
    hlt

; GDT Data
    
gdt_data:
	DQ	0x0000000000000000
	DQ	0x00CF9A000000FFFF
	DQ	0x00CF92000000FFFF
	DQ	0x0000000000000000
	DQ	0x00A09A0000000000
	DQ	0x00A0920000000000
 
gdt_r1:
	DW	23
	DD	gdt_data
 
gdt_r2:
	DW	23
	DD	gdt_data + 24
	DD	0
 
gdt_r3:
	DW	23
	DQ	gdt_data + 24 + 0xFFFFFFFF80000000