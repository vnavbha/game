#pragma once

#include "game/app/engineappcommon.h"

class ZAppWindow;

//-----------------------------------------------------------------------------

class ZEngineApp : public ZEngineAppCommon
{
public:
	ZEngineApp();
	virtual ~ZEngineApp();

protected:
	virtual void Init();
	virtual void Uninit();

private:
	void InitWorkspace();
};