#ifndef _IO_H
#define _IO_H

unsigned char inportb(unsigned short port);
unsigned short inportw(unsigned short port);
unsigned long inportdw(unsigned short port);
void outportb(unsigned short port, unsigned char data);
void outportw(unsigned short port, unsigned short data);
void outportdw(unsigned short port, unsigned long data);

unsigned long read_cr0();
unsigned long read_cr2();
unsigned long read_cr3();
void write_cr0(unsigned long d);
void write_cr2(unsigned long d);
void write_cr3(unsigned long d);

#endif // _IO_H