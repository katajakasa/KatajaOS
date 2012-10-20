#include <system/panic.h>
#include <devices/video/console.h>
#include <system/cpu.h>
#include <kprintf.h>

void panic(const char* str) {
    console_setvt(KLOGVT);
    kprintf("Kernel panic: ");
    kprintf(str);
    cpu_nop();
    cpu_int_disable();
    cpu_halt();
}
