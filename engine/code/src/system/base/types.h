#ifndef _ZTYPES_H_
#define _ZTYPES_H_

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


// ----------------------------------------------------------------------------

typedef unsigned int uint32;
typedef int int32;
typedef unsigned char uint8;

typedef unsigned char byte;

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
#define ZFnFindIf eastl::findif
#define ZFnMakePair eastl::make_pair

#endif