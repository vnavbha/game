#include "memory.h"
#include "dlmalloc.h"
#include <stdlib.h>

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

void operator delete[](void *p, size_t size)
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
	void *mem = dlmalloc(size + alignment-1);
	void *ptr = (void*)(((uintptr_t)mem + (alignment - 1)) & ~(uintptr_t)0x0F);
	return ptr;
}