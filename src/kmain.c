#include "system/multiboot2.h"
#include "system/idt.h"
#include "devices/video/screen.h"
#include "devices/video/console.h"
#include "mem/pmm.h"
#include "kprintf.h"

void kmain(unsigned long magic, multiboot_info_t* mbt2_info) {
    // Initialize video
    screen_init();
    console_init();

    // Check multiboot header
    if(magic == MULTIBOOT2_BOOTLOADER_MAGIC) {
        kprintf("kmain.c: Found Multiboot2 header (0x%lx)!\n", magic);
    } else {
        kprintf("kmain.c: No valid multiboot2 header detected!\n");
        return;
    }
    
    // Other stuff
    idt_init();
    pmm_init(mbt2_info);
}
