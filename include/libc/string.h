#ifndef _STRING_H
#define _STRING_H

#include <stddef.h>

size_t strlen(const char *s);
int strcmp(const char *s1, const char *s2);
void* memccpy(void *dest, const void *src, int c, size_t n);
void* memchr (const void *s, int c, size_t n);
int   memcmp (const void *s1, const void *s2, size_t n);
void* memcpy (void *dest, const void *src, size_t n);
void* memmove(void *dest, const void *src, size_t n);
void* memset (void *s, int c, size_t n);

#endif // _STRING_H