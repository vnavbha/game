#pragma once

#include "../build_runtime_render.h"
#include "../renderswapchainbase.h"

#include <d3d11.h>

//-----------------------------------------------------------------------------

class RUNTIME_RENDER_API ZRenderSwapChain : public ZRenderSwapChainBase
{
public:
	ZRenderSwapChain();
	virtual ~ZRenderSwapChain();

	bool Init(const ZRenderDevice* pDevice) override;
	void Uninit() override;

private:
	DXGI_SWAP_CHAIN_DESC m_desc;
	IDXGISwapChain* m_pSwapChain;
	bool m_bVsyncEnabled;
};