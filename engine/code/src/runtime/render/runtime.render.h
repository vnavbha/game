#pragma once
#include "system/base/subsystem/subsystem.h"

class ZRenderDevice;

//-----------------------------------------------------------------------------

class ZRenderSubSystem : public ZSubSystem
{
public:
	ZRenderSubSystem();
	~ZRenderSubSystem();

	bool Init() override;
	void Uninit() override;
	void Update(const SGameTime& gameTime) override;

	ZRenderDevice* GetRenderDevice();

protected:
	ZRenderDevice* m_pRenderDevice;
};
