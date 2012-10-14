#include <devices/video/console.h>

unsigned int active_vt;
unsigned char color;
char *prompt = "@:>\0";

typedef struct vterm {
    unsigned int x;
    unsigned int y;
    unsigned int cmdpos;
    char* cmdline[CMDLINELEN];
    char* vtbuffer[VTVIEWLEN];
} terminal_t;

terminal_t vts[VTCOUNT];

void console_cmdlineadd(const char c) {
    if(active_vt == 0)
        return;

    char* addr;
    if(vts[active_vt].cmdpos > CMDLINELEN) {
        vts[active_vt].cmdpos--;
    }

    switch(c) {
        case 0x08: // Backspace
            if(vts[active_vt].cmdpos < 1) break;
            vts[active_vt].cmdpos--;
            addr = (char *)(*vts[active_vt].cmdline + vts[active_vt].cmdpos);
            *addr = 0;
            break;

        default:
            addr = (char *)(*vts[active_vt].cmdline + vts[active_vt].cmdpos);
            *addr = c;
            vts[active_vt].cmdpos++;
            break;
    }
    console_flush();
}

void console_cmdlineclear() {
    if(active_vt == 0)
        return;

    console_print(active_vt, prompt, strlen(prompt));
    if(vts[active_vt].cmdpos > 0) {
        console_print(active_vt, *vts[active_vt].cmdline, vts[active_vt].cmdpos);
        memset(*vts[active_vt].cmdline, 0, CMDLINELEN);
        vts[active_vt].cmdpos = 0;
    } else {
        console_print(active_vt, "\n", 1);
    }
    console_flush();
}

void console_init() {
    active_vt = 0;
    console_setcolor(COLOR_WHITE|COLOR_INTENSITY_LOW, COLOR_BLACK);
    int i;
    for(i = 0; i < VTCOUNT; i++) {
        console_clear(i);
        vts[i].x = 0;
        vts[i].y = 0;
        vts[i].cmdpos = 0;
        memset(vts[i].cmdline, 0, CMDLINELEN);
    }
    console_setvt(0);
}

void console_flush() {
    unsigned int ccnt  = vts[active_vt].y * VTCOLS + vts[active_vt].x;
    screen_clear();
    screen_print(color, 0, (char *)vts[active_vt].vtbuffer, ccnt);
    if(active_vt != 0) {
        screen_print(color, ccnt, prompt, strlen(prompt));
        screen_print(color, ccnt + strlen(prompt), *vts[active_vt].cmdline, vts[active_vt].cmdpos);
        screen_move_cursor(ccnt + vts[active_vt].cmdpos + strlen(prompt));
    } else {
        screen_move_cursor(ccnt);
    }
}

void console_scroll(unsigned int vt) {
    unsigned int line;
    vts[vt].y--;
    volatile char *addr = (char *)vts[vt].vtbuffer;
    for(line = 1; line < VTROWS; line++) {
        memcpy((char*)(addr + (line-1) * VTCOLS), (char*)(addr + line * VTCOLS), VTCOLS);

        // Tarvittaessa tyhjennetään rivi
        if(line == VTROWS-1) {
            int i = 0;
            while(i < VTCOLS) {
                *(addr + line * VTCOLS + i++) = ' ';
            }
        }
    }
}

unsigned int console_getvt() {
    return active_vt;
}

void console_setvt(unsigned int vt) {
    active_vt = vt;
    console_flush();
}

void console_print(unsigned int vt, char* str, unsigned int len) {
    unsigned int i = 0;
	while(i < len) {
	    console_putch(vt, *(str + i++));
	}
}

void console_putch(unsigned int vt, char c) {
    volatile char *addr = (char *)vts[vt].vtbuffer;
    switch(c) {
        case '\n': // Line feed
            vts[vt].y++;
            if(vts[vt].y >= VTROWS) {
                console_scroll(vt);
            }
            vts[vt].x = 0;
            break;

        case 0x08: // Backspace
            if(vts[vt].x < 1 && vts[vt].y < 1)
                break;

            if(vts[vt].x < 1) {
                vts[vt].y--;
                vts[vt].x = VTCOLS-1;
            } else {
                vts[vt].x--;
            }
            *(addr + vts[vt].x + vts[vt].y * VTCOLS) = ' ';
            break;

        case 0x09: // Tab
            vts[vt].x = (vts[vt].x + 8) & ~(8 - 1);
            break;

        case '\r': // Carriage return
            vts[vt].x = 0;
            break;

        default:
            *(addr + vts[vt].x + vts[vt].y * VTCOLS) = c;
            if(vts[vt].x < VTCOLS-1) {
                vts[vt].x++;
            } else {
                vts[vt].x = 0;
                vts[vt].y++;
                if(vts[vt].y >= VTROWS) {
                    console_scroll(vt);
                }
            }
            break;
    }
}

void console_clear(unsigned int vt) {
    volatile char *addr = (char *)vts[vt].vtbuffer;
    int i = 0;
    while(i < VTVIEWLEN) {
        *(addr + i++) = ' ';
    }
}

void console_setcolor(char fore, char back) {
    color = fore|(back<<4);
}
