#include <devices/video/screen.h>

void screen_init() {
    screen_clear();
}

void screen_putch(unsigned char color, unsigned int pos, char c) {
    volatile char *addr = (volatile char*)(0xB8000L + pos*2);
    if(pos*2 < SCREEN_SIZE) {
        *addr++ = c;
        *addr++ = color;
    }
}

void screen_clear() {
    int i = 0;
    volatile char *addr = (volatile char*)0xB8000;
    while(i < SCREEN_SIZE) {
        *(addr + i++) = ' ';
        *(addr + i++) = 0x7;
    }
    screen_move_cursor(0);
}

void screen_print(unsigned char color, unsigned int pos, char* str, unsigned int len) {
    unsigned int i = pos*2, b = 0;
    volatile char *addr = (volatile char *)0xB8000;
    while(b < len && i < SCREEN_SIZE) {
        *(addr + i++) = *(str + b++);
        *(addr + i++) = color;
    }
}

void screen_move_cursor(unsigned int pos) {
   outportb(0x3D4, 0x0F);
   outportb(0x3D5, (unsigned char)(pos & 0xFF));
   outportb(0x3D4, 0x0E);
   outportb(0x3D5, (unsigned char )((pos >> 8) & 0xFF));
}
