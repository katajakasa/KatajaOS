#ifndef _SCREEN_H
#define _SCREEN_H

#include <system/io.h>
#include <string.h>

#define SCREEN_ROWS 25
#define SCREEN_COLS 80
#define SCREEN_SIZE (SCREEN_COLS*SCREEN_ROWS*2)

#define COLOR_INTENSITY_HIGH 0x8
#define COLOR_INTENSITY_LOW 0x0
#define COLOR_WHITE 0x7
#define COLOR_YELLOW 0x6
#define COLOR_MAGENTA 0x5
#define COLOR_RED 0x4
#define COLOR_CYAN 0x3
#define COLOR_GREEN 0x2
#define COLOR_BLUE 0x1
#define COLOR_BLACK 0x0

void screen_init();
void screen_putch(unsigned char color, unsigned int pos, char c);
void screen_move_cursor(unsigned int pos);
void screen_print(unsigned char color, unsigned int pos, char* str, unsigned int len);
void screen_clear();

#endif // _SCREEN_H