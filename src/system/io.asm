[BITS 64]

global inportb
global outportb
global inportw
global outportw
global inportdw
global outportdw

global read_cr0
global read_cr2
global read_cr3
global write_cr0
global write_cr2
global write_cr3

inportb:
    mov rdx, [rsp+8]
    xor rax, rax
    in al, dx
    ret

outportb:
    mov rdx, [rsp+8]
    mov rax, [rsp+16]
    out dx, al
    ret

inportw:
    mov rdx, [rsp+8]
    xor rax, rax
    in ax, dx
    ret

outportw:
    mov rdx, [rsp+8]
    mov rax, [rsp+16]
    out dx, ax
    ret

inportdw:
    mov rdx, [rsp+8]
    in eax, dx
    ret

outportdw:
    mov rdx, [rsp+8]
    mov rax, [rsp+16]
    out dx, eax
    ret

read_cr0:
    mov rax, cr0
    retn

write_cr0:
    push rbp
    mov rbp, rsp
    mov rax, [rbp+8]
    mov cr0,  rax
    pop rbp
    retn

read_cr2:
    mov rax, cr2
    retn

write_cr2:
    push rbp
    mov rbp, rsp
    mov rax, [rbp+8]
    mov cr2, rax
    pop rbp
    retn
    
read_cr3:
    mov rax, cr3
    retn

write_cr3:
    push rbp
    mov rbp, rsp
    mov rax, [rbp+8]
    mov cr3, rax
    pop rbp
    retn
