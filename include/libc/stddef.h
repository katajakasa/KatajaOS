#ifndef _STDDEF_H
#define _STDDEF_H

#undef NULL
#define NULL ((void*)0)

typedef unsigned long size_t;
typedef long ptrdiff_t;
typedef unsigned int wchar_t;

#define offsetof(st, m) ((size_t)((char*)&((st*)(0))->m - (char*)0))

#endif // _STDDEF_H