#include "system.resource.h"
#include "system/base/debug/debug.h"
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

