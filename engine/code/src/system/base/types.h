#ifndef _ZTYPES_H_
#define _ZTYPES_H_

#pragma once

#include "eastl/utility.h"
#include "eastl/string.h"
#include "eastl/map.h"
#include "eastl/vector.h"
#include "eastl/array.h"
#include "eastl/algorithm.h"


// ----------------------------------------------------------------------------


typedef unsigned int uint32;
typedef int int32;
typedef unsigned char uint8;

typedef unsigned char byte;

// EASTL
using ZString = eastl::string;
using ZWString = eastl::wstring;

template<typename T1, typename T2>
using TPair = eastl::pair<T1, T2>;

template <typename T, size_t N = 1>
using TFixedArray = eastl::array<T, N>;

template <typename T, typename Allocator = EASTLAllocatorType>
using TArray = eastl::vector<T, Allocator>;

template <typename Key, typename T, typename Compare = eastl::less<Key>, typename Allocator = EASTLAllocatorType >
using TMap = eastl::map<Key, T, Compare, Allocator>;

#define TFind eastl::find
#define TFindIf eastl::findif
#define TPair eastl::make_pair

#endif