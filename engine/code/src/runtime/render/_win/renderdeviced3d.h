#pragma once

#include <d3d11.h>
#include "../renderdevicebase.h"
#include "renderswapchaind3d.h"

class ZAppWindow;

class ZRenderDevice : public ZRenderDeviceBase
{
public:
	ZRenderDevice();
	virtual ~ZRenderDevice();

	bool Init(ZAppWindow* pWindow) override;
	void Uninit() override;

	const ZAppWindow* GetWindow() const;

	IDXGIFactory* GetDXGIFactory() const;
	ID3D11Device* GetD3DDevice() const;

private:
	bool InitDXGIFactory();
	void UninitDXGIFactory();

	bool InitDeviceCaps();
	void UninitDeviceCaps();
	
	bool InitDevice();
	void UninitDevice();

	bool InitSwapChain();
	void UninitSwapChain();
	
private:
	ZAppWindow* m_pWindow;

	IDXGIFactory* m_pFactory;
	ID3D11Device* m_pDevice;
	ZRenderSwapChain m_swapChain;
	
	D3D_FEATURE_LEVEL m_featureLevel;
};