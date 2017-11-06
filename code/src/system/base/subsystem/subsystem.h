#pragma once

#include "../build_system_base.h"

//-----------------------------------------------------------------------------

struct STime;

class SYSTEM_BASE_API ZSubSystem
{
public:
	ZSubSystem();
	virtual ~ZSubSystem();

	virtual bool Init();
	virtual void Uninit();
	virtual void Update(const STime& time);
};
