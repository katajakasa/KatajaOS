#ifndef _REGISTERS_H
#define _REGISTERS_H

struct registers_t {
	unsigned long gs, fs;
	unsigned long rax, rbx, rcx, rdx, rdi, rsi, rbp, rsp;
    unsigned long r8, r9, r10, r11, r12, r13, r14, r15;
	unsigned long rflags;
    unsigned long int_no, error_code;
};

void dump_registers(struct registers_t *regs);

#endif // _REGISTERS_H