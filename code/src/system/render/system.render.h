#pragma once

#include "build_system_render.h"

#include "system/base/subsystem/subsystem.h"
#include "system/base/types.h"

//-----------------------------------------------------------------------------

class SYSTEM_RENDER_API ZSystemRenderSubSystem : public ZSubSystem
{
public:
	ZSystemRenderSubSystem();
	virtual ~ZSystemRenderSubSystem();

	bool Init() override;
	void Uninit() override;
	void Update(const STime& time) override;

protected:
};
