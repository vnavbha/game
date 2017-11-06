#pragma once

#include "system/resource/resourceid.h"

struct SPackParams
{
	ZResourceId m_ridSource;
	ZResourceId m_ridTarget;
};

class ZMeshPacker
{
public:
	ZMeshPacker();
	~ZMeshPacker();

	bool Pack(const SPackParams& params);
};
