#pragma once
#include "build_runtime_render.h"
#include "system/base/subsystem/subsystem.h"

class ZRenderDevice;

//-----------------------------------------------------------------------------

class RUNTIME_RENDER_API ZRuntimeRenderSubSystem : public ZSubSystem
{
public:
	ZRuntimeRenderSubSystem();
	~ZRuntimeRenderSubSystem();

	bool Init() override;
	void Uninit() override;
	void Update(const STime& time) override;

	ZRenderDevice* GetRenderDevice();

protected:
	ZRenderDevice* m_pRenderDevice;
};
