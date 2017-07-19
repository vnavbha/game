#include "runtime.render.h"
#include "renderdevice.h"

#include "runtime/app/appbase.h"
#include "system/base/debug/debug.h"

//-----------------------------------------------------------------------------

ZRenderSubSystem::ZRenderSubSystem()
	: m_pRenderDevice(nullptr)
{

}

ZRenderSubSystem::~ZRenderSubSystem()
{
	ZASSERT(m_pRenderDevice == nullptr);
}

//-----------------------------------------------------------------------------

bool ZRenderSubSystem::Init()
{
	ZAppWindow* pWindow = GetApp()->GetWindow();
	
	m_pRenderDevice = ZNEW ZRenderDevice();
	if (!m_pRenderDevice->Init(pWindow))
	{
		return false;
	}

	return ZSubSystem::Init();
}

void ZRenderSubSystem::Uninit()
{
	m_pRenderDevice->Uninit();
	ZDELETE(m_pRenderDevice);
	m_pRenderDevice = nullptr;
	ZSubSystem::Uninit();
}

void ZRenderSubSystem::Update(const SGameTime& gameTime)
{
	ZSubSystem::Update(gameTime);
}

ZRenderDevice* ZRenderSubSystem::GetRenderDevice()
{
	return m_pRenderDevice;
}
