#include "system/render/system.render.h"

//-----------------------------------------------------------------------------

ZSystemRenderSubSystem::ZSystemRenderSubSystem()
{

}

ZSystemRenderSubSystem::~ZSystemRenderSubSystem()
{

}

bool ZSystemRenderSubSystem::Init()
{
	return ZSubSystem::Init();
}

void ZSystemRenderSubSystem::Uninit()
{
	ZSubSystem::Uninit();
}

void ZSystemRenderSubSystem::Update(const STime& time)
{
	ZSubSystem::Update(time);
}
