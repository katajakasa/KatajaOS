#include <kprintf.h>
#include <devices/video/console.h>

int uint2hex(unsigned long num, char *buf, int bufsize, int uppercase) {
    int i = bufsize;
    do {
        if(uppercase)
            buf[--i] = "0123456789ABCDEF"[num & 0x0f];
        else
            buf[--i] = "0123456789abcdef"[num & 0x0f];
        num >>= 4;
    } while(num);

    memmove(buf, buf + i, bufsize - i);
    buf[bufsize - i] = 0;
    return bufsize - i;
}

int uint2str(unsigned long num, char *buf, int bufsize) {
    if(!num) {
        buf[0] = '0';
        buf[1] = 0;
        return 1;
    }
 
    int i = bufsize;
    do {
        buf[--i] = (num % 10) + '0';
        num /= 10;
    } while (num);
    
    memmove(buf, buf + i, bufsize - i);
    buf[bufsize - i] = 0;
    return bufsize - i;
}

int kprintf(const char *fmt, ...) {
    int ret = 0;

    char r_c;
    char *r_s;
    int r_ui;
    char output[32];
    int output_len;
    
    va_list args;
    va_start(args, fmt);
    while (*fmt) {
        switch (*fmt) {
            case '%':
                if(!(char*)(fmt+1)) {
                    console_putch(KLOGVT,'%');
                    ret++;
                    break;
                }

                switch(*(++fmt)) {
                    // Character
                    case 'c':
                        r_c = va_arg(args, int);
                        console_putch(KLOGVT, r_c);
                        ret++;
                        break;
                        
                    case 'l':
                        if(!(char*)(fmt+1)) {
                            console_putch(KLOGVT,'%');
                            ret++;
                            break;
                        }
                        switch(*(++fmt)) {
                            // Signed long decimal integer
                            case 'd':
                            case 'i':
                            
                            // Unsigned long decimal integer
                            case 'u':
                                r_ui = va_arg(args, long);
                                output_len = uint2str(r_ui, output, 32);
                                console_print(KLOGVT, output, output_len);
                                ret += output_len;
                                break;
                                
                            // Lowercase long unsigned hexadecimal integer
                            case 'x':
                                r_ui = va_arg(args, long);
                                output_len = uint2hex(r_ui, output, 32, 0);
                                console_print(KLOGVT, output, output_len);
                                ret += output_len;
                                break;
                            
                            // Uppercase long unsigned hexadecimal integer
                            case 'X':
                                r_ui = va_arg(args, long);
                                output_len = uint2hex(r_ui, output, 32, 1);
                                console_print(KLOGVT, output, output_len);
                                ret += output_len;
                                break;
                                
                            // Unknown
                            default:
                                console_putch(KLOGVT,*fmt);
                                ret++;
                                break;
                        }
                        break;
                        
                    // Signed decimal integer (fall to unsigned for now)
                    case 'd':
                    case 'i':
                    
                    // Unsigned decimal integer
                    case 'u':
                        r_ui = va_arg(args, int);
                        output_len = uint2str(r_ui, output, 32);
                        console_print(KLOGVT, output, output_len);
                        ret += output_len;
                        break;
                        
                    // Lowercase unsigned hexadecimal integer
                    case 'x':
                        r_ui = va_arg(args, int);
                        output_len = uint2hex(r_ui, output, 32, 0);
                        console_print(KLOGVT, output, output_len);
                        ret += output_len;
                        break;
                    
                    // Uppercase unsigned hexadecimal integer
                    case 'X':
                        r_ui = va_arg(args, int);
                        output_len = uint2hex(r_ui, output, 32, 1);
                        console_print(KLOGVT, output, output_len);
                        ret += output_len;
                        break;

                    // String
                    case 's':
                        r_s = va_arg(args, char*);
                        console_print(KLOGVT, r_s, strlen(r_s));
                        ret += strlen(r_s);
                        break;
                        
                    // %
                    case '%':
                        console_putch(KLOGVT, '%');
                        ret++;
                        break;
                        
                    // Unknown
                    default:
                        console_putch(KLOGVT,*fmt);
                        ret++;
                        break;
                }
                fmt++;
                break;

            default:
                console_putch(KLOGVT,*fmt);
                fmt++;
                ret++;
                break;
        }
    }
    va_end(args);
    console_flush();
    return ret;
}
