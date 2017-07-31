#include "engineapp.h"

#include "runtime/render/runtime.render.h"

#include "system/base/types.h"
#include "system/resource/system.resource.h"

#include <windows.h>
#include <string>

//-----------------------------------------------------------------------------

ZEngineApp::ZEngineApp()
{

}

ZEngineApp::~ZEngineApp()
{
	
}

void ZEngineApp::Init()
{
	ZEngineAppCommon::Init();
	InitWorkspace();
}

void ZEngineApp::Uninit()
{

}

void ZEngineApp::InitWorkspace()
{
	wchar_t pStr[MAX_PATH];
	GetModuleFileName(NULL, pStr, MAX_PATH);
	
	m_exePath = ZFilePath(ZString().assign_convert(pStr));
	OnExecutablePathInitialized();
}
