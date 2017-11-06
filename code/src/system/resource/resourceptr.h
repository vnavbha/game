#pragma once

#include "build_system_resource.h"
#include "system/base/ptr/sharedptr.h"

class ZResourceData;

//-----------------------------------------------------------------------------

class SYSTEM_RESOURCE_API ZResourcePtr
{
public:
	ZResourcePtr();
	ZResourcePtr(TSharedPtr<const ZResourceData> pData);
	~ZResourcePtr();

	const ZResourceData* GetResourceData() const;

	bool IsNull() const;

private:
	TSharedPtr< const ZResourceData > m_pData;
};

//-----------------------------------------------------------------------------