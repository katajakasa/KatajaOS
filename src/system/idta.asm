[BITS 64]

global idt_load
extern isr_handler

; ISR Handler
isr_ahandler:
    ; Push registers
    pushfq
    push r15
    push r14
    push r13
    push r12
    push r11
    push r10
    push r9
    push r8
    push rsp
    push rbp
    push rsi
    push rdi
    push rdx
    push rcx
    push rbx
    push rax
    push fs
    push gs

    ; Call handler
    mov rdi, rsp
    push rdi
    call isr_handler
    pop rdi

    ; Pop registers
    pop gs
    pop fs
    pop rax
    pop rbx
    pop rcx
    pop rdx
    pop rdi
    pop rsi
    pop rbp
    pop rsp
    pop r8
    pop r9
    pop r10
    pop r11
    pop r12
    pop r13
    pop r14
    pop r15
    popfq
    
    ; "Remove" errorcode and interrupt number from stack
    add rsp, 16
    
    ; You haf to get out of here!
    iretq

; Loads IDT (Duh!)
idt_load:
    lidt [rdi]
    ret

; ISR with no error message (first 8 interrupts)
%macro isr_0 1
global isr%1
isr%1:
    push qword 0
    push qword %1
    jmp isr_ahandler
%endmacro

; ISR with an error message (Last 8 interrupts)
%macro isr_8 1
global isr%1
isr%1:
    push qword %1
    jmp isr_ahandler
%endmacro

; ISR Handlers (created with macros)
isr_0 0
isr_0 1
isr_0 2
isr_0 3
isr_0 4
isr_0 5
isr_0 6
isr_0 7
isr_8 8
isr_8 9
isr_8 10
isr_8 11
isr_8 12
isr_8 13
isr_8 14
isr_8 15
isr_8 16
isr_8 17
isr_8 18
isr_8 19
isr_8 20
isr_8 21
isr_8 22
isr_8 23
isr_8 24
isr_8 25
isr_8 26
isr_8 27
isr_8 28
isr_8 29
isr_8 30
isr_8 31
