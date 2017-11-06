#include "memory.h"

//-----------------------------------------------------------------------------
//

ZAllocator g_globalAllocator;

void* operator new(size_t size, const char* pSzDebug, ZAllocator* pAllocator)
{
	return pAllocator->allocate(size);
}

void* operator new[](size_t size, const char* pSzDebug, ZAllocator* pAllocator)
{
	return pAllocator->allocate(size);
}

void operator delete(void* p, const char* pSzDebug, ZAllocator* pAllocator)
{
	pAllocator->deallocate(p);
}

void operator delete[](void* p, ZAllocator* pAllocator)
{
	pAllocator->deallocate(p);
}
