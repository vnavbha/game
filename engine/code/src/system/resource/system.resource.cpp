#include "system.resource.h"
#include "system/base/debug/debug.h"
#include "system/base/app/appbase.h"
#include <string>

#if defined(WINDOWS)
#include <Windows.h>
#endif

//-----------------------------------------------------------------------------

ZResourceSubSystem::ZResourceSubSystem()
{

}

ZResourceSubSystem::~ZResourceSubSystem()
{

}

//-----------------------------------------------------------------------------

bool ZResourceSubSystem::Init()
{
	ZFilePath path = GetApp()->GetExePath();
	m_resourcePath = path.GetDirectory() + GetApp()->GetApplicationOption<ZString>("RESOURCE_PATH");

	ZASSERT(m_resourcePath.IsValid());
	return true;
}

void ZResourceSubSystem::Uninit()
{
	ZSubSystem::Uninit();
}

void ZResourceSubSystem::Update(const SGameTime& gameTime)
{
	ZSubSystem::Update(gameTime);
}

