#pragma once
#include "../build_system_base.h"

struct STime;

//-----------------------------------------------------------------------------

class SYSTEM_BASE_API ZAppWindowBase
{
public:
	ZAppWindowBase();
	virtual ~ZAppWindowBase();

	virtual bool Init();
	virtual void Uninit();
	virtual bool Update(const STime& time);

private:
};
