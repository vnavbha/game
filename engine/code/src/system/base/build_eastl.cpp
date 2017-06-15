#include "EASTL/internal/config.h"
#include <memory>

void* operator new[](size_t size, const char* pName, int flags,
	unsigned debugFlags, const char* file, int line)
{
	return malloc(size);
}
void* operator new[](size_t size, size_t alignment, size_t alignmentOffset,
const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{
	// this allocator doesn't support alignment
	EASTL_ASSERT(alignment <= 8);
	return malloc(size);
}

// EASTL also wants us to define this (see string.h line 197)
int Vsnprintf8(char8_t* pDestination, size_t n, const char8_t* pFormat, va_list arguments)
{
#ifdef _MSC_VER
	return _vsnprintf_s(pDestination, n, n, pFormat, arguments);
#else
	return _vsnprintf_s(pDestination, n, n, pFormat, arguments);
#endif
}	