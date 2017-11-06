#pragma once

#include "build_runtime_render.h"

class ZRenderDevice;

class RUNTIME_RENDER_API ZRenderSwapChainBase
{
public:
	ZRenderSwapChainBase();
	virtual ~ZRenderSwapChainBase();

	virtual bool Init(const ZRenderDevice* pDevice) = 0;
	virtual void Uninit() = 0;
};
