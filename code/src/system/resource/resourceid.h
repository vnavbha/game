#pragma once

#include "build_system_resource.h"
#include "system/base/types.h"

//-----------------------------------------------------------------------------

class SYSTEM_RESOURCE_API ZResourceId
{
public:
	ZResourceId(const ZString& sRid);
	~ZResourceId();

	bool IsValid() const;
	uint64 Hash() const;
	const ZString& ToString() const;
	
private:
	ZString m_rid;
};
