global inportb
global outportb
global inportw
global outportw
global inportdw
global outportdw
global read_cr0
global write_cr0
global read_cr3
global write_cr3
global read_cr2

inportb:
        mov edx, [esp+4]
        xor eax, eax
        in al, dx
        ret

outportb:
        mov edx, [esp+4]
        mov eax, [esp+8]
        out dx, al
        ret

inportw:
        mov edx, [esp+4]
        xor eax, eax
        in ax, dx
        ret

outportw:
        mov edx, [esp+4]
        mov eax, [esp+8]
        out dx, ax
        ret

inportdw:
        mov edx, [esp+4]
        in eax, dx
        ret

outportdw:
        mov edx, [esp+4]
        mov eax, [esp+8]
        out dx, eax
        ret
