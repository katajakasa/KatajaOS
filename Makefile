# A simple Makefile for KatajaOS

# Change these as necessary
CROSS=/usr/local/cross/bin/
OUTPUT=bin/kernel.bin

# Tools
NASM=nasm
CC=$(CROSS)/x86_64-pc-elf-gcc
RM=rm -f
MKDIR=mkdir -p
MV=mv
LD=$(CROSS)/x86_64-pc-elf-ld

# Files
BOOTSTRAPFILE=src/bootstrap/bootstrap.asm
FILES := \
    src/kmain.c
    
# Directories
BINDIR=bin
INCDIR=include
OBJDIR=obj

# Flags
NASMFLAGS=-felf64
CFLAGS=-I$(INCDIR) -m64 -ffreestanding -nostdlib -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -mno-sse3 -mno-3dnow 
LDFLAGS=-nostdlib -nodefaultlibs -T scripts/link.ld

all: 
	$(MKDIR) $(BINDIR)/
	$(MKDIR) $(OBJDIR)/
	$(NASM) $(NASMFLAGS) -o $(OBJDIR)/bootstrap.o $(BOOTSTRAPFILE)
	$(CC) $(CFLAGS) -c $(FILES)
	$(MV) *.o $(OBJDIR)/
	$(LD) $(LDFLAGS) -o $(OUTPUT) $(OBJDIR)/*.o
	@echo "All done!"

clean:
	$(RM) $(OBJDIR)/*.o
	$(RM) $(LIBDIR)/*

