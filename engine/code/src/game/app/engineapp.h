#pragma once

#include "runtime/app/appbase.h"

//-----------------------------------------------------------------------------

class ZEngineApp : public ZAppBase
{
public:
	ZEngineApp();
	virtual ~ZEngineApp();

protected:
	virtual void Init();
	virtual void Uninit();
};