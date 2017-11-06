#pragma once

#include "../build_system_base.h"
#include "dlmalloc.h"

#include "EABase/config/eacompilertraits.h"
#include "EASTL/type_traits.h"
#include "EASTL/internal/smart_ptr.h"

//-----------------------------------------------------------------------------

//extern void* operator new(size_t size);
//extern void operator delete(void *p);
//extern void* operator new[](size_t size);
//extern void operator delete[](void *p, size_t size);
//
//extern void* operator new[](size_t size, const char* pName, int flags,
//	unsigned debugFlags, const char* file, int line);
//
//extern void* operator new[](size_t size, size_t alignment, size_t alignmentOffset,
//	const char* pName, int flags, unsigned debugFlags, const char* file, int line);
//
//#define ZNEW new
//#define ZPLACEMENT_NEW(p) new(p)
//#define ZNEW_ARRAY(type, size) new type[size]
//
//#define ZDELETE(p) delete p;
//#define ZDELETE_ARRAY(p) delete[] p;
//
//#define DEFINE_NEW_OPERATORS																\
//																							\
//void* operator new(size_t size)																\
//{																							\
//	return dlmalloc(size);																	\
//}																							\
//																							\
//void operator delete(void *p)																\
//{																							\
//	dlfree(p);																				\
//}																							\
//																							\
//void* operator new[](size_t size)															\
//{																							\
//	return dlmalloc(size);																	\
//}																							\
//																							\
//void operator delete[](void *p, size_t size)												\
//{																							\
//	dlbulk_free(&p, size);																	\
//}																							\
//																							\
//void* operator new[](size_t size, const char* pName, int flags,								\
//	unsigned debugFlags, const char* file, int line)										\
//{																							\
//	return dlmalloc(size);																	\
//}																							\
//																							\
//void* operator new[](size_t size, size_t alignment, size_t alignmentOffset,					\
//	const char* pName, int flags, unsigned debugFlags, const char* file, int line)			\
//{																							\
//	void *mem = dlmalloc(size + alignment - 1);												\
//	void *ptr = (void*)(((uintptr_t)mem + (alignment - 1)) & ~(uintptr_t)0x0F);				\
//	return ptr;																				\
//}																							

class SYSTEM_BASE_API ZAllocator
{
public:
	ZAllocator(const char* pName = NULL) { m_pName = pName; }
	ZAllocator(const ZAllocator& alloc) { m_pName = alloc.m_pName; }
	ZAllocator(const ZAllocator&, const char* pName) { m_pName = pName; }

	ZAllocator& operator=(const ZAllocator&) { return *this; }

	void* allocate(size_t n, int flags = 0) { return dlmalloc(n); }
	void* allocate(size_t n, size_t alignment, size_t offset, int flags = 0)
	{
		void *mem = dlmalloc(n + alignment - 1);
		void *ptr = (void*)(((uintptr_t)mem + (alignment - 1)) & ~(uintptr_t)0x0F);
		return ptr;
	}

	void  deallocate(void* p, size_t n)
	{
		dlfree(p);
	}

	void  deallocate(void* p)
	{
		dlfree(p);
	}

	const char* get_name() const { return m_pName; }
	void        set_name(const char* pName) { m_pName = pName; }

private:
	const char* m_pName;
};

inline bool operator==(const ZAllocator& a, const ZAllocator& b)
{
	return false;
}

inline bool operator!=(const ZAllocator& a, const ZAllocator& b)
{
	return true;
}

//-----------------------------------------------------------------------------

extern SYSTEM_BASE_API ZAllocator g_globalAllocator;
SYSTEM_BASE_API void* operator new(size_t size, const char* pSzDebug, ZAllocator* pAllocator);
SYSTEM_BASE_API void* operator new[] (size_t size, const char* pSzDebug, ZAllocator* pAllocator);
SYSTEM_BASE_API void operator delete(void* p, const char* pSzDebug, ZAllocator* pAllocator);
SYSTEM_BASE_API void operator delete[](void* p, ZAllocator* pAllocator);

template<typename T>
void ZDelete(T* p)
{
	delete(p);
}

template<typename T>
void ZDeleteArray(T* p)
{
	delete[](p);
}

template <typename T>
class ZDeleteHelper
{
public:
	void operator()(T* p)
	{
		ZDelete(p);
	}
};

// dlmalloc temp disabled
#define ZNEW new /*new("overlaoaded", &g_globalAllocator)*/
#define ZDELETE delete /*ZDelete*/
#define ZDELETE_ARRAY delete[]/*ZDeleteArray*/