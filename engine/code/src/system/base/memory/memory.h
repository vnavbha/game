#ifndef _ZALLOCATOR_H_
#define _ZALLOCATOR_H_
#pragma once

#include "../build_system_base.h"

#include "../types.h"

//-----------------------------------------------------------------------------

extern void* operator new(size_t size);
extern void operator delete(void *p);
extern void* operator new[](size_t size);
extern void operator delete[](void *p, size_t size);

extern void* operator new[](size_t size, const char* pName, int flags,
	unsigned debugFlags, const char* file, int line);

extern void* operator new[](size_t size, size_t alignment, size_t alignmentOffset,
	const char* pName, int flags, unsigned debugFlags, const char* file, int line);

extern void* operator new(size_t size);
extern void operator delete(void *p);
extern void* operator new[](size_t size);
extern void operator delete[](void *p, size_t size);

extern void* operator new[](size_t size, const char* pName, int flags,
	unsigned debugFlags, const char* file, int line);

extern void* operator new[](size_t size, size_t alignment, size_t alignmentOffset,
	const char* pName, int flags, unsigned debugFlags, const char* file, int line);

#define ZNEW new
#define ZPLACEMENT_NEW(p) new(p)
#define ZNEW_ARRAY(type, size) new type[size]

#define ZDELETE(p) delete p;
#define ZDELETE_ARRAY(p) delete[] p;

#endif // _ALLOCATOR_H_