# A simple Makefile for KatajaOS

# Change these as necessary
CROSS=/usr/local/cross/bin
OUTPUT=kernel.bin

# Tools
NASM=nasm
CC=$(CROSS)/x86_64-pc-elf-gcc
RM=rm -f
MKDIR=mkdir -p
MV=mv
CP=cp
LD=$(CROSS)/x86_64-pc-elf-ld

# Files
BOOTSTRAPFILE=src/bootstrap/bootstrap.asm
FILES := \
    src/kmain.c
    
# Directories
INCDIR=include
OBJDIR=obj
ISODIR=iso

# Flags
NASMFLAGS=-felf64
CFLAGS=-I$(INCDIR) \
    -m64 \
    -ffreestanding \
    -fno-builtin \
    -nostdlib \
    -mcmodel=kernel \
    -mno-red-zone \
    -mno-mmx \
    -mno-sse \
    -mno-sse2 \
    -mno-sse3 \
    -mno-3dnow \
    -Wall \
    -Wextra
LDFLAGS=-nostdlib -nodefaultlibs -T scripts/link.ld

all: 
	$(MKDIR) $(BINDIR)/
	$(MKDIR) $(OBJDIR)/
	$(NASM) $(NASMFLAGS) -o $(OBJDIR)/bootstrap.o $(BOOTSTRAPFILE)
	$(CC) $(CFLAGS) -c $(FILES)
	$(MV) *.o $(OBJDIR)/
	$(LD) $(LDFLAGS) -o $(ISODIR)/boot/$(OUTPUT) $(OBJDIR)/*.o
	@echo "All done!"

image:
	grub-mkrescue -o image.iso $(BINDIR)
    
clean:
	$(RM) $(OBJDIR)/*.o
	$(RM) $(BINDIR)/image.bin

