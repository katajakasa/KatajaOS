global inportb
global outportb
global inportw
global outportw
global inportdw
global outportdw

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
