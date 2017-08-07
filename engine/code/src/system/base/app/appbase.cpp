#include "appbase.h"
#include "runtime/render/renderdevice.h"
#include "system/base/time/time.h"
#include "system/base/app/appwindow.h"
#include "system/base/memory/memory.h"
#include "system/base/debug/debug.h"
#include "system/base/subsystem/subsystem.h"


//-----------------------------------------------------------------------------

namespace
{
	ZAppBase* g_pApp = nullptr;
}

//-----------------------------------------------------------------------------

ZAppBase::ZAppBase()
{
}

ZAppBase::~ZAppBase()
{

}

void ZAppBase::Init()
{
	ZFilePath exePath = ZFilePath(m_exePath.GetDirectory() + ZFilePath::PathSeparator() + "engine.ini");
	ZASSERT(exePath.IsValid());
	m_iniFile.Init(exePath);

	m_pWindow = ZNEW ZAppWindow();
	m_pWindow->Init();

	m_aSubSystems.fill(nullptr);
}

void ZAppBase::Uninit()
{
	m_pWindow->Uninit();
	ZDELETE(m_pWindow);
	m_pWindow = nullptr;

	m_aSubSystems.fill(nullptr);
}

void ZAppBase::Run()
{
	bool bExit = false;
	while (!bExit)
	{
		if (!Update())
		{
			bExit = true;
		};
	}
}

bool ZAppBase::Update()
{
	SGameTime dummy;
	for (auto* pSubSystem : m_aSubSystems)
	{
		pSubSystem->Update(dummy);
	}
	return true;
}

ZAppWindow* ZAppBase::GetWindow() const
{
	return m_pWindow;
}

const ZFilePath ZAppBase::GetExePath() const
{
	return m_exePath;
}

void ZAppBase::UnregisterSubSystem(ESubSystems id)
{
	m_aSubSystems[id]->Uninit();
	ZDELETE(m_aSubSystems[id]);
	m_aSubSystems[id] = nullptr;
}

ZAppBase* GetApp()
{
	return g_pApp;
}

void SetApp(ZAppBase* pApp)
{
	ZASSERT(g_pApp != pApp);
	g_pApp = pApp;
}
