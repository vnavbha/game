#pragma once

#include "system/resource/build_system_resource.h"
#include "system/base/types.h"
#include "system/base/collections/buffer.h"

class ZResourceId;

//-----------------------------------------------------------------------------

class SYSTEM_RESOURCE_API ZResourceData
{
public:
	ZResourceData(ZBuffer&& data);
	ZResourceData(ZResourceData&& data);
	ZResourceData& operator=(ZResourceData&& rhs);

	~ZResourceData();	

	const ZBuffer& GetData() const;

private:
	ZBuffer m_data;
};
