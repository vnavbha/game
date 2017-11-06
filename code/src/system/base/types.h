#pragma once

#include "build_system_base.h"
#include "eastl/utility.h"
#include "eastl/array.h"
#include "eastl/fixed_hash_map.h"
#include "eastl/queue.h"
#include "eastl/deque.h"
#include "eastl/string.h"
#include "eastl/map.h"
#include "eastl/hash_map.h"
#include "eastl/hash_set.h"
#include "eastl/vector.h"
#include "eastl/algorithm.h"
#include "EABase/config/eacompilertraits.h"
EA_DISABLE_VC_WARNING(4996)
#include "EAStdC/EAString.h"
EA_RESTORE_VC_WARNING()
#include "EASTL/functional.h"

// Primarily for eastl. 
// Relates to compiler warnings about exposing interfaces to collections declared as member variables.
// Never use a member collections directly without providing an interface.
#define DISABLE_EASTL_WARNINGS  \
EA_DISABLE_VC_WARNING(4251)

DISABLE_EASTL_WARNINGS

#include "math/vector.h"
#include "math/matrix.h"
#include "math/quaternion.h"
#include "math/rect.h"

#include "memory/memory.h"


// ----------------------------------------------------------------------------

typedef unsigned long long uint64;
typedef long long int64;

typedef unsigned int uint32;
typedef int int32;

typedef float float32;

typedef unsigned char ubyte; 

//-----------------------------------------------------------------------------
// Math
//-----------------------------------------------------------------------------

typedef Vector<float32, 2> ZVector2;
typedef Vector<float32, 3> ZVector3;
typedef Vector<float32, 4> ZVector4;
typedef Vector<int32, 2> ZVector2i;
typedef Vector<int32, 3> ZVector3i;
typedef Vector<int32, 4> ZVector4i;

typedef Matrix<float, 2, 2> ZMatrix22;
typedef Matrix<float, 3, 3> ZMatrix33;
typedef Matrix<float, 4, 4> ZMatrix44;

typedef VectorPacked<float, 2> ZPackedVector2;
typedef VectorPacked<float, 3> ZPackedVector3;
typedef VectorPacked<float, 4> ZPackedVector4;

typedef VectorPacked<int, 2> ZPackedVector2i;
typedef VectorPacked<int, 3> ZPackedVector3i;
typedef VectorPacked<int, 4> ZPackedVector4i;

typedef Quaternion<float> ZQuaternion;

typedef Rect<float> ZRectF;
typedef Rect<int> ZRectI;

//-----------------------------------------------------------------------------
// EASTL
//-----------------------------------------------------------------------------

using ZString = eastl::basic_string<char, ZAllocator>;
using ZWString = eastl::basic_string<wchar_t, ZAllocator>;
using ZStringHash = eastl::hash<ZString>;

template<typename T1, typename T2>
using TPair = eastl::pair<T1, T2>;

template <typename T, size_t N = 1>
using TFixedArray = eastl::array<T, N>;

template <typename T>
using TArray = eastl::vector<T, ZAllocator>;

template <typename T>
using TArrayRef = const TArray<T>&;

template <typename Key, typename T, size_t nodeCount, size_t bucketCount = nodeCount + 1, bool bEnableOverflow = true,
	typename Hash = eastl::hash<Key>, typename Predicate = eastl::equal_to<Key>, bool bCacheHashCode = false>
using TFixedHashMap = eastl::fixed_hash_map<Key, T, nodeCount, bucketCount, false,
	Hash, Predicate, bCacheHashCode, ZAllocator>;

template <typename T, typename Container = eastl::deque<T, ZAllocator, DEQUE_DEFAULT_SUBARRAY_SIZE(T)> >
using TQueue = eastl::queue<T, Container>;

template <typename T, unsigned kDequeSubarraySize = DEQUE_DEFAULT_SUBARRAY_SIZE(T)>
using TDequeue = eastl::deque<T, ZAllocator, kDequeSubarraySize>;

template <typename Key, typename T, typename Compare = eastl::less<Key>>
using TMap = eastl::map<Key, T, Compare, ZAllocator>;

namespace eastl
{
	template <>
	struct hash<ZString>
	{
		size_t operator()(const ZString& x) const
		{
			const unsigned char* p = (const unsigned char*)x.c_str(); // To consider: limit p to at most 256 chars.
			unsigned int c, result = 2166136261U; // We implement an FNV-like string hash. 
			while ((c = *p++) != 0) // Using '!=' disables compiler warnings.
				result = (result * 16777619) ^ c;
			return (size_t)result;
		}
	};
}

template <typename Key, typename T, bool bCacheHashCode = false>
using THashMap = eastl::hash_map<Key, T, eastl::hash<Key>, eastl::equal_to<Key>, ZAllocator>;

template <typename Value, typename Hash = eastl::hash<Value>, typename Predicate = eastl::equal_to<Value>, bool bCacheHashCode = false>
using THashSet = eastl::hash_set<Value, Hash, Predicate, ZAllocator>;

//-----------------------------------------------------------------------------

#define ZFnFind eastl::find
#define ZFnFindIf eastl::find_if
#define ZFnMakePair eastl::make_pair
#define ZFnToInt EA::StdC::AtoI32
#define ZFnToUInt EA::StdC::AtoU32
#define ZFnICmp EA::StdC::Stricmp
#define ZFnCmp EA::StdC::StrCmp

EA_RESTORE_VC_WARNING()