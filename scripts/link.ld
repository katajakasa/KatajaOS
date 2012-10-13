OUTPUT_FORMAT(elf64-x86-64)
ENTRY(bootstrap)
KERNEL_BASE = 0xFFFFFFFF80000000;
KERNEL_LMA = 0x100000;
SECTIONS
{
    . = KERNEL_LMA;

    .bootstrap :
    {
		*(.header)
        *(.boot)
		. = ALIGN(4096);
		pos_pml4 = .;
		. += 0x1000;
		pos_pdpt = .;
		. += 0x1000;
		pos_pd = .;
		. += 0x1000;
		. += 0x8000;
		pos_stack = .;
    }

    . += KERNEL_BASE;

	.text ALIGN(0x1000) : AT(ADDR(.text) - KERNEL_BASE)
	{
		*(.text)
		*(.gnu.linkonce.t*)
	}
	
	.data ALIGN(0x1000) : AT(ADDR(.data) - KERNEL_BASE)
	{
		*(.data)
		*(.gnu.linkonce.d*)
	}
	
	.rodata ALIGN(0x1000) : AT(ADDR(.rodata) - KERNEL_BASE)
	{
		*(.rodata*)
		*(.gnu.linkonce.r*)
	}
	
	.bss ALIGN(0x1000) : AT(ADDR(.bss) - KERNEL_BASE)
	{
		*(COMMON)
		*(.bss)
		*(.gnu.linkonce.b*)
	}
	
	/DISCARD/ :
	{
		*(.comment)
		*(.eh_frame)
	}
}
