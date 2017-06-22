#include "memory.h"
#include "dlmalloc.h"

//-----------------------------------------------------------------------------

void* operator new(size_t size)
{
	return dlmalloc(size);
}

void operator delete(void *p)
{
	dlfree(p);
}

void* operator new[](size_t size)
{
	return dlmalloc(size);
}

extern void operator delete[](void *p, size_t size)
{
	dlbulk_free(&p, size);
}

void* operator new[](size_t size, const char* pName, int flags,
	unsigned debugFlags, const char* file, int line)
{
	return dlmalloc(size);
}

void* operator new[](size_t size, size_t alignment, size_t alignmentOffset,
	const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{
	return dlmemalign(size, alignment);
}