#include "renderswapchaind3d.h"
#include "renderdeviced3d.h"
#include "system/base/types.h"
#include "system/base/debug/debug.h"

#include "system/base/app/appwindow.h"

//-----------------------------------------------------------------------------

ZRenderSwapChain::ZRenderSwapChain()
	: m_bVsyncEnabled(true)
{

}

ZRenderSwapChain::~ZRenderSwapChain()
{

}

bool ZRenderSwapChain::Init(const ZRenderDevice* pDevice)
{
	ZeroMemory(&m_desc, sizeof(m_desc));

	// Set to a single back buffer.
	m_desc.BufferCount = 1;

	// Set the width and height of the back buffer.
	m_desc.BufferDesc.Width = pDevice->GetWindow()->GetWidth();
	m_desc.BufferDesc.Height = pDevice->GetWindow()->GetHeight();

	// Set regular 32-bit surface for the back buffer.
	m_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// Set the refresh rate of the back buffer.
	const TArray<SDisplayDesc>& aSupportedDisplays = pDevice->GetDeviceCaps().m_aSupportedDisplays;
	auto fnFind = [&](const SDisplayDesc& lhs)
	{
		return
			lhs.m_nWidth == m_desc.BufferDesc.Width &&
			lhs.m_nHeight == m_desc.BufferDesc.Height;
	};
	auto it = ZFnFindIf(aSupportedDisplays.begin(), aSupportedDisplays.end(), fnFind);
	if (it == aSupportedDisplays.end())
	{
		ZTRACE_MESSAGE("renderswapchaind3d", "unable to find supported display desc, vsync is disabled");
		m_bVsyncEnabled = false;
	}
	if (m_bVsyncEnabled)
	{
		
		m_desc.BufferDesc.RefreshRate.Numerator = it->m_nRefreshRateNumerator;
		m_desc.BufferDesc.RefreshRate.Denominator = it->m_nRefreshRateDenominator;
	}
	else
	{
		m_desc.BufferDesc.RefreshRate.Numerator = 0;
		m_desc.BufferDesc.RefreshRate.Denominator = 1;
	}

	m_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	m_desc.OutputWindow = pDevice->GetWindow()->GetHandle();

	// Turn multisampling off.
	m_desc.SampleDesc.Count = 1;
	m_desc.SampleDesc.Quality = 0;
	// Set to full screen or windowed mode.
	if (pDevice->GetWindow()->IsFullScreen())
	{
		m_desc.Windowed = false;
	}
	else
	{
		m_desc.Windowed = true;
	}
	m_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	m_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// Discard the back buffer contents after presenting.
	m_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// Don't set the advanced flags.
	m_desc.Flags = 0;
	HRESULT hresult = pDevice->GetDXGIFactory()->CreateSwapChain(
		pDevice->GetD3DDevice(),
		&m_desc,
		&m_pSwapChain
	);

	if (FAILED(hresult))
	{
		ZTRACE_MESSAGE("renderswapchaind3d", "failed to create render swap chain");
		return false;
	}

	return true;
}

void ZRenderSwapChain::Uninit()
{
	if (m_pSwapChain != nullptr)
	{
		m_pSwapChain->Release();
		m_pSwapChain = 0;
	}

}
