#include "system/multiboot2.h"
#include "screen.h"

void kmain(unsigned long magic, multiboot_info_t* mbt2_info) {
    screen_init();
    screen_print(COLOR_INTENSITY_HIGH|COLOR_BLUE, 0, "LOLWIN", 6);
}
