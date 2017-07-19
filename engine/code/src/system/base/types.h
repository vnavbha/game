#pragma once

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
#include "eastl/shared_ptr.h"
#include "math/vector.h"
#include "math/matrix.h"
#include "math/quaternion.h"
#include "math/rect.h"


// ----------------------------------------------------------------------------

typedef unsigned int uint32;
typedef int int32;
typedef unsigned char uint8;

typedef float float32;

typedef unsigned char byte;

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


using ZString = eastl::string;
using ZWString = eastl::wstring;

template <typename T>
using TSharedPtr = eastl::shared_ptr<T>;

template<typename T1, typename T2>
using TPair = eastl::pair<T1, T2>;

template <typename T, size_t N = 1>
using TFixedArray = eastl::array<T, N>;

template <typename T, typename Allocator = EASTLAllocatorType>
using TArray = eastl::vector<T, Allocator>;

template <typename T>
using TArrayRef = const TArray<T>&;

template <typename Key, typename T, size_t nodeCount, size_t bucketCount = nodeCount + 1, bool bEnableOverflow = true,
	typename Hash = eastl::hash<Key>, typename Predicate = eastl::equal_to<Key>, bool bCacheHashCode = false, typename OverflowAllocator = EASTLAllocatorType>
using TFixedHashMap = eastl::fixed_hash_map<Key, T, nodeCount, bucketCount, false,
	Hash, Predicate, bCacheHashCode, OverflowAllocator>;

template <typename T, typename Container = eastl::deque<T, EASTLAllocatorType, DEQUE_DEFAULT_SUBARRAY_SIZE(T)> >
using TQueue = eastl::queue<T, Container>;

template <typename T, typename Allocator = EASTLAllocatorType, unsigned kDequeSubarraySize = DEQUE_DEFAULT_SUBARRAY_SIZE(T)>
using TDequeue = eastl::deque<T, Allocator, kDequeSubarraySize>;

template <typename Key, typename T, typename Compare = eastl::less<Key>, typename Allocator = EASTLAllocatorType >
using TMap = eastl::map<Key, T, Compare, Allocator>;

template <typename Key, typename T, typename Hash = eastl::hash<Key>, typename Predicate = eastl::equal_to<Key>,
	typename Allocator = EASTLAllocatorType, bool bCacheHashCode = false>
using THashMap = eastl::hash_map<Key, T, Hash, Predicate, Allocator>;

template <typename Value, typename Hash = eastl::hash<Value>, typename Predicate = eastl::equal_to<Value>,
	typename Allocator = EASTLAllocatorType, bool bCacheHashCode = false>
using THashSet = eastl::hash_set<Value, Hash, Predicate, Allocator>;

//-----------------------------------------------------------------------------

#define ZFnFind eastl::find
#define ZFnFindIf eastl::find_if
#define ZFnMakePair eastl::make_pair
