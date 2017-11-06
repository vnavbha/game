#include "engineappcommon.h"

#include "runtime/render/runtime.render.h"

#include "system/resource/system.resource.h"
#include "system/render/system.render.h"

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
	
	REGISTER_SUBSYSTEM(ZSystemResourceSubSystem,			SS_SYSTEM_RESOURCE);
	REGISTER_SUBSYSTEM(ZSystemRenderSubSystem,				SS_SYSTEM_RENDER);	
	REGISTER_SUBSYSTEM(ZRuntimeRenderSubSystem,				SS_RUNTIME_RENDER);
}

void ZEngineAppCommon::Uninit()
{
	UNREGISTER_SUBSYSTEM(ZRuntimeRenderSubSystem,			SS_RUNTIME_RENDER);
	UNREGISTER_SUBSYSTEM(ZSystemRenderSubSystem,			SS_SYSTEM_RENDER);
	UNREGISTER_SUBSYSTEM(ZSystemResourceSubSystem,			SS_SYSTEM_RESOURCE);

	ZAppBase::Uninit();
}
