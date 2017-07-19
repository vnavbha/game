#include "engineapp.h"

#include "runtime/render/runtime.render.h"

//-----------------------------------------------------------------------------

ZEngineApp::ZEngineApp()
{

}

ZEngineApp::~ZEngineApp()
{

}

//-----------------------------------------------------------------------------

void ZEngineApp::Init()
{
	ZAppBase::Init();

	REGISTER_SUBSYSTEM(ZRenderSubSystem, SS_RUNTIME_RENDER);	
}

void ZEngineApp::Uninit()
{
	UNREGISTER_SUBSYSTEM(ZRenderSubSystem, SS_RUNTIME_RENDER);

	ZAppBase::Uninit();
}
