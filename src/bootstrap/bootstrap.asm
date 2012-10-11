[BITS 32]
[GLOBAL bootstrap]
 
ALIGN 8
mb_header_start:
    ; Header
	DD	0xE85250D6
	DD	0
	DD	mb_header_end - mb_header_start
	DD	-(0xE85250D6 + (mb_header_end - mb_header_start))
    
	DW	0, 0
	DD	8
mb_header_end:

bootstrap:
    hlt

