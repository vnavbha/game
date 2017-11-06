#include "runtime.render.h"
#include "renderdevice.h"

#include "system/base/app/appbase.h"
#include "system/base/debug/debug.h"

//-----------------------------------------------------------------------------

ZRuntimeRenderSubSystem::ZRuntimeRenderSubSystem()
	: m_pRenderDevice(nullptr)
{

}

ZRuntimeRenderSubSystem::~ZRuntimeRenderSubSystem()
{
	ZASSERT(m_pRenderDevice == nullptr);
}

//-----------------------------------------------------------------------------

bool ZRuntimeRenderSubSystem::Init()
{
	ZAppWindow* pWindow = GetApp()->GetWindow();
	
	m_pRenderDevice = ZNEW ZRenderDevice();
	if (!m_pRenderDevice->Init(pWindow))
	{
		return false;
	}

	return ZSubSystem::Init();
}

void ZRuntimeRenderSubSystem::Uninit()
{
	m_pRenderDevice->Uninit();
	ZDELETE(m_pRenderDevice);
	m_pRenderDevice = nullptr;
	ZSubSystem::Uninit();
}

void ZRuntimeRenderSubSystem::Update(const STime& time)
{
	ZSubSystem::Update(time);
}

ZRenderDevice* ZRuntimeRenderSubSystem::GetRenderDevice()
{
	return m_pRenderDevice;
}
