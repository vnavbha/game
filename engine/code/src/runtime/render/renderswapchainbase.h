#pragma once

class ZRenderDevice;

class ZRenderSwapChainBase
{
public:
	ZRenderSwapChainBase();
	virtual ~ZRenderSwapChainBase();

	virtual bool Init(const ZRenderDevice* pDevice) = 0;
	virtual void Uninit() = 0;
};
