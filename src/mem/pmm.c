#include "mem/pmm.h"
#include "system/multiboot2.h"
#include "system/panic.h"
#include "kprintf.h"

unsigned long ram_size;

void pmm_init(multiboot_info_t* mbt2_info) {
    // Check if mmap info is available
    if(!(mbt2_info->flags & MULTIBOOT_INFO_MEM_MAP)) {
        kprintf("pmm.c: MMap not available, using linear ram.\n");
        ram_size = mbt2_info->mem_lower + mbt2_info->mem_upper;
    } else {
        kprintf("pmm.c: MMap Addr = 0x%x Len = 0x%x\n", mbt2_info->mmap_addr, mbt2_info->mmap_length);
        unsigned int mmap_done = 0;
        multiboot_memory_map_t *ptr;
        while(mmap_done < mbt2_info->mmap_length) {
            ptr = (multiboot_memory_map_t*)((unsigned long)mbt2_info->mmap_addr + mmap_done);
            
            kprintf("pmm.c: Area %lx, %lx\n", ptr->addr, ptr->len);
            
            ram_size += ptr->len;
            mmap_done += ptr->size;
        }
    }
    
    // Make sure we have at least some :)
	if(ram_size == 0) {
	    panic("No RAM detected!\n");
	}
    
    // Report RAM
    kprintf("pmm.c: %lu MBytes of RAM found.\n", ram_size);
}

unsigned long get_ram_size() {
    return ram_size;
}

