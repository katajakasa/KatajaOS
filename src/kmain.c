#include "system/multiboot.h"
#include "system/idt.h"
#include "devices/video/screen.h"
#include "devices/video/console.h"
#include "mem/pmm.h"
#include "kprintf.h"

void kmain(unsigned long magic, multiboot_info_t* mbt_info) {
    // Initialize video
    screen_init();
    console_init();

    // Check multiboot header
    if(magic == MULTIBOOT_BOOTLOADER_MAGIC) {
        kprintf("kmain.c: Found Multiboot header (0x%lx)!\n", magic);
    } else {
        kprintf("kmain.c: No valid multiboot header detected!\n");
        return;
    }
    
    // Other stuff
    idt_init();
    pmm_init(mbt_info);
}
