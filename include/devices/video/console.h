#ifndef _CONSOLE_H
#define _CONSOLE_H

#include <devices/video/screen.h>
#include <string.h>

#define KLOGVT 0
#define VTCOUNT 2
#define VTROWS SCREEN_ROWS
#define VTCOLS SCREEN_COLS
#define VTVIEWLEN (VTCOLS*VTROWS)
#define CMDLINELEN 64

void console_init();
void console_print(unsigned int vt, char* str, unsigned int len);
void console_putch(unsigned int vt, char c);
void console_clear(unsigned int vt);
void console_setcolor(char fore, char back);
void console_flush();

void console_cmdlineadd(char c);
void console_cmdlineclear();

unsigned int console_getvt();
void console_setvt(unsigned int n);

#endif // _CONSOLE_H