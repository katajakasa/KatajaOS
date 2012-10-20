#include <system/registers.h>
#include <kprintf.h>

void dump_registers(struct registers_t *regs) {
	kprintf("Dumping registers:\n");
	kprintf("  rax = 0x%lx  rbx = 0x%lx  rcx = 0x%lx  rdx = 0x%lx\n", regs->rax, regs->rbx, regs->rcx, regs->rdx);
    kprintf("  r8 = 0x%lx  r9 = 0x%lx  r10 = 0x%lx  r11 = 0x%lx\n", regs->r8,  regs->r9,  regs->r10, regs->r11);
    kprintf("  r12 = 0x%lx  r13 = 0x%lx  r14 = 0x%lx  r15 = 0x%lx\n", regs->r12, regs->r13, regs->r14, regs->r15);
    kprintf("  rsi = 0x%lx  rdi = 0x%lx  rsp = 0x%lx  rbp = 0x%lx\n", regs->rsi, regs->rdi, regs->rsp, regs->rbp);
    kprintf("  fs = 0x%lx  gs = 0x%lx  rflags = 0x%lx\n", regs->fs,  regs->gs,  regs->rflags);
}
