#pragma once

#include "EABase/config/eacompilertraits.h"
EA_DISABLE_VC_WARNING(4251)

#include "system/base/build_system_base.h"
#include "system/base/memory/memory.h"
#include "eastl/shared_ptr.h"

//-----------------------------------------------------------------------------

template <typename T>
using TSharedPtr = eastl::shared_ptr<T>;

template<typename T>
TSharedPtr<T> TSharedPtrCreate(T* p)
{
	ZDeleteHelper<T> d;
	return eastl::shared_ptr<T>(p, d, g_globalAllocator);
}
