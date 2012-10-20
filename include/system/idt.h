#ifndef _IDT_H
#define _IDT_H

struct registers_t;

struct idt_entry {
    unsigned short base_lo;
    unsigned short sel;
    unsigned char always0;
    unsigned char flags;
    unsigned short base_mid;
    unsigned int base_hi;
    unsigned int always0_2;
} __attribute__((packed));

struct idt_ptr {
    unsigned short limit;
    unsigned long base;
} __attribute__((packed));

struct isr_t {
	const char *name;
	void (*handler)(struct registers_t *regs);
};

struct idt_entry idt[256];
struct idt_ptr idtp;

extern void idt_load(struct idt_ptr *addr);
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
void idt_init(void);

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

#endif // _IDT_H
