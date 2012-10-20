#ifndef _PMM_H
#define _PMM_H

typedef struct multiboot_info multiboot_info_t;

void pmm_init(multiboot_info_t* mbt2_info);
unsigned long get_ram_size();

#endif