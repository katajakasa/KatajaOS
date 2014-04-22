#include <system/idt.h>
#include <system/panic.h>
#include <system/io.h>
#include <system/registers.h>
#include <string.h>
#include <kprintf.h>

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags) {
    idt[num].base_lo = (base & 0xFFFF);
    idt[num].base_mid = (base >> 16) & 0xFFFF;
    idt[num].base_hi = (base >> 32) & 0xFFFFFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].always0_2 = 0;
    idt[num].flags = flags;
}

void idt_init(void) {
    idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
    idtp.base = (unsigned long)&idt;
    memset(&idt, 0, sizeof(struct idt_entry) * 256); // Clear IDT

    idt_set_gate(0,  (unsigned long)isr0,  0x08, 0x8E);
    idt_set_gate(1,  (unsigned long)isr1,  0x08, 0x8E);
    idt_set_gate(2,  (unsigned long)isr2,  0x08, 0x8E);
    idt_set_gate(3,  (unsigned long)isr3,  0x08, 0x8E);
    idt_set_gate(4,  (unsigned long)isr4,  0x08, 0x8E);
    idt_set_gate(5,  (unsigned long)isr5,  0x08, 0x8E);
    idt_set_gate(6,  (unsigned long)isr6,  0x08, 0x8E);
    idt_set_gate(7,  (unsigned long)isr7,  0x08, 0x8E);
    idt_set_gate(8,  (unsigned long)isr8,  0x08, 0x8E);
    idt_set_gate(9,  (unsigned long)isr9,  0x08, 0x8E);
    idt_set_gate(10, (unsigned long)isr10, 0x08, 0x8E);
    idt_set_gate(11, (unsigned long)isr11, 0x08, 0x8E);
    idt_set_gate(12, (unsigned long)isr12, 0x08, 0x8E);
    idt_set_gate(13, (unsigned long)isr13, 0x08, 0x8E);
    idt_set_gate(14, (unsigned long)isr14, 0x08, 0x8E);
    idt_set_gate(15, (unsigned long)isr15, 0x08, 0x8E);
    idt_set_gate(16, (unsigned long)isr16, 0x08, 0x8E);
    idt_set_gate(17, (unsigned long)isr17, 0x08, 0x8E);
    idt_set_gate(18, (unsigned long)isr18, 0x08, 0x8E);
    idt_set_gate(19, (unsigned long)isr19, 0x08, 0x8E);
    idt_set_gate(20, (unsigned long)isr20, 0x08, 0x8E);
    idt_set_gate(21, (unsigned long)isr21, 0x08, 0x8E);
    idt_set_gate(22, (unsigned long)isr22, 0x08, 0x8E);
    idt_set_gate(23, (unsigned long)isr23, 0x08, 0x8E);
    idt_set_gate(24, (unsigned long)isr24, 0x08, 0x8E);
    idt_set_gate(25, (unsigned long)isr25, 0x08, 0x8E);
    idt_set_gate(26, (unsigned long)isr26, 0x08, 0x8E);
    idt_set_gate(27, (unsigned long)isr27, 0x08, 0x8E);
    idt_set_gate(28, (unsigned long)isr28, 0x08, 0x8E);
    idt_set_gate(29, (unsigned long)isr29, 0x08, 0x8E);
    idt_set_gate(30, (unsigned long)isr30, 0x08, 0x8E);
    idt_set_gate(31, (unsigned long)isr31, 0x08, 0x8E);
    idt_load(&idtp);

    kprintf("idt.c: IDT installed.\n");
}

void page_fault_handler(struct registers_t *rgs) {
    void* cr2 = (void*)read_cr2();
    dump_registers(rgs);
    kprintf("Trying to %s address 0x%x; %s. Processor is in %s mode.\n",
        ((rgs->error_code & 0x2) ? "write" : "read"),
        cr2,
        ((rgs->error_code & 0x1) ? "page is not present" : "page-level protection violation"),
        ((rgs->error_code & 0x4) ? "user" : "supervisor"));
    panic("Pagefault is deadly for now.");
}

void div_by_zero_handler(struct registers_t *regs) {
    dump_registers(regs);
    panic("Oh shi-! Division By Zero.");
}

void double_fault_handler(struct registers_t *regs) {
    dump_registers(regs);
    panic("Doublefault is deadly. Need moar reboot.");
}

void invalid_opcode_handler(struct registers_t *regs) {
    dump_registers(regs);
    panic("Invalid Opcode. Wtf?");
}

struct isr_t isrs[32] = {
    {"Division by zero", div_by_zero_handler},
    {"Debug exception", 0},
    {"Non-maskable interrupt", 0},
    {"Breakpoint", 0},
    {"INTO-detected overflow", 0},
    {"Out of bounds", 0},
    {"Invalid opcode", invalid_opcode_handler},
    {"No coprocessor", 0},
    {"Double fault", double_fault_handler},
    {"Coprocessor segment overrun", 0},
    {"Invalid task state segment", 0},
    {"Segment not present", 0},
    {"Stack exception", 0},
    {"General protection fault", 0},
    {"Page fault", page_fault_handler},
    {"Unknown interrupt", 0},
    {"Floating point error", 0},
    {"Alignment check", 0},
    {"Machine check", 0},
    {"Reserved", 0},
    {"Reserved", 0},
    {"Reserved", 0},
    {"Reserved", 0},
    {"Reserved", 0},
    {"Reserved", 0},
    {"Reserved", 0},
    {"Reserved", 0},
    {"Reserved", 0},
    {"Reserved", 0},
    {"Reserved", 0},
    {"Reserved", 0},
    {"Reserved", 0}
};

void isr_handler(struct registers_t *rgs) {
    if (rgs->int_no & 0xffffffe0) {
        panic("isr.c: isr_handler got an invalid interrupt!");
    }
    if (isrs[rgs->int_no].handler) {
        isrs[rgs->int_no].handler(rgs);
    } else {
        kprintf("isr.c: ISR %i not handled correctly!", rgs->int_no);
    }
}
