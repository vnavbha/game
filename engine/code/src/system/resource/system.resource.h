#pragma once
#include "system/base/subsystem/subsystem.h"
#include "system/base/stream/filepath.h"
#include "system/base/types.h"

class ZRenderDevice;

//-----------------------------------------------------------------------------

class ZResourceSubSystem : public ZSubSystem
{
public:
	ZResourceSubSystem();
	~ZResourceSubSystem();

	bool Init() override;
	void Uninit() override;
	void Update(const SGameTime& gameTime) override;
	
protected:
	ZFilePath m_resourcePath;
};
