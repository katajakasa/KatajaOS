# A simple Makefile for KatajaOS

CROSS=/usr/local/cross/bin/
OUTPUT=bin/kernel.bin

NASM=nasm
CC=$(CROSS)/x86_64-pc-elf-gcc
RM=rm -f
MKDIR=mkdir -p
MV=mv
LD=$(CROSS)/x86_64-pc-elf-ld

FILES := \
    src/kmain.c
    
BINDIR=bin
INCDIR=include
OBJDIR=obj

CFLAGS=-I$(INCDIR) -m64 -ffreestanding -nostdlib -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -mno-sse3 -mno-3dnow 
LDFLAGS=-nostdlib -nodefaultlibs -T scripts/link.ld

all: 
	$(MKDIR) $(BINDIR)/
	$(MKDIR) $(OBJDIR)/
	$(CC) $(CFLAGS) -c $(FILES)
	$(MV) *.o $(OBJDIR)/
	$(LD) $(LDFLAGS) -o $(OUTPUT) $(OBJDIR)/*.o
	@echo "All done!"

clean:
	$(RM) $(OBJDIR)/*.o
	$(RM) $(LIBDIR)/*

