BITS 32
global cpu_nop
global cpu_int_enable
global cpu_int_disable
global cpu_halt

cpu_nop:
    nop
    ret

cpu_int_disable:
    cli
    ret

cpu_int_enable:
    sti
    ret

cpu_halt:
    hlt
    ret
