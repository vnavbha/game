#include "engineappcommon.h"

#include "runtime/render/runtime.render.h"
#include "system/resource/system.resource.h"

//-----------------------------------------------------------------------------

ZEngineAppCommon::ZEngineAppCommon()
{

}

ZEngineAppCommon::~ZEngineAppCommon()
{

}

//-----------------------------------------------------------------------------

void ZEngineAppCommon::Init()
{
	ZAppBase::Init();
	
	REGISTER_SUBSYSTEM(ZResourceSubSystem, SS_SYSTEM_RESOURCE);
	REGISTER_SUBSYSTEM(ZRenderSubSystem, SS_RUNTIME_RENDER);
}

void ZEngineAppCommon::Uninit()
{
	UNREGISTER_SUBSYSTEM(ZRenderSubSystem, SS_RUNTIME_RENDER);
	UNREGISTER_SUBSYSTEM(ZResourceSubSystem, SS_SYSTEM_RESOURCE);

	ZAppBase::Uninit();
}
