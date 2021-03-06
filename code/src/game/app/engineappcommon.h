#pragma once

#include "system/base/app/appbase.h"

class ZAppWindow;

//-----------------------------------------------------------------------------

class ZEngineAppCommon : public ZAppBase
{
public:
	ZEngineAppCommon();
	virtual ~ZEngineAppCommon();

protected:
	virtual void Init() override;
	virtual void Uninit() override;
};