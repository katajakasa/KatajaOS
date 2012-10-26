#include "mem/pmm.h"
#include "system/multiboot.h"
#include "system/panic.h"
#include "kprintf.h"

unsigned long ram_size;

#define MULTIBOOT_MMAP_EXISTS 0x40
#define MULTIBOOT_RSIZE_EXISTS 0x01

void pmm_init(multiboot_info_t* mbt) {
    // Check if mmap info is available
    if((mbt->flags & MULTIBOOT_MMAP_EXISTS) == 1) {
        kprintf("pmm.c: MMap found @ 0x%lx, length: 0x%lx\n", mbt->mmap_addr, mbt->mmap_length);
        
        multiboot_memory_map_t* mmap = (multiboot_memory_map_t*)mbt->mmap_addr;
        while(mmap < mbt->mmap_addr + mbt->mmap_length) {
            mmap = (multiboot_memory_map_t*)(mmap + mmap->size + 4);
            kprintf("pmm.c: Area %lx - %lx, type: %u\n", mmap->addr, (mmap->addr + mmap->len), mmap->type);
            ram_size += mmap->len;
        }
    }
    
    // No memory map, check linear
    if(ram_size == 0 && (mbt->flags & MULTIBOOT_RSIZE_EXISTS) == 1) {
        kprintf("pmm.c: No multiboot memory map.\n");
        ram_size = (mbt->mem_lower + mbt->mem_upper) * 1024;
    }
    
    // Make sure we have at least some :)
	if(ram_size == 0) {
	    panic("No RAM detected!\n");
	}
    
    // Report RAM
    kprintf("pmm.c: %lu MBytes of RAM found.\n", (ram_size / 1024 / 1024));
}

unsigned long get_ram_size() {
    return ram_size;
}

