#ifndef _STDARG_H
#define _STDARG_H

typedef struct va_list_s {
	void* va_ptr;
} va_list;

#define va_start(ap, argN) ((ap.va_ptr = (void*)(&argN + 1)),(void)0)
#define va_copy(dest, src) ((dest.va_ptr = src.va_ptr),(void)0)
#define va_arg(ap, type) ((ap.va_ptr = ((char*)ap.va_ptr + sizeof(type))), *(type*)((char*)ap.va_ptr - sizeof(type)))
#define va_end(ap) ((ap.va_ptr = 0),(void)0)

#endif // _STDARG_H