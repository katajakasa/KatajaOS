#include "system/multiboot2.h"
#include "devices/video/screen.h"
#include "devices/video/console.h"
#include "kprintf.h"

void kmain(unsigned long magic, multiboot_info_t* mbt2_info) {
    // Initialize video
    screen_init();
    console_init();

    // Check multiboot header
    if(magic == MULTIBOOT2_BOOTLOADER_MAGIC) {
        kprintf("Found Multiboot2 header (0x%lx)!\n", magic);
    } else {
        kprintf("Error! No valid multiboot2 header detected!\n");
        return;
    }
}
