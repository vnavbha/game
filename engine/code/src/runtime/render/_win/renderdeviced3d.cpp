#include "renderdeviced3d.h"
#include "system/base/debug/debug.h"

#define _RELEASE(p)		{ if(p){(p)->Release(); (p)=nullptr;} }
#define _RELEASE_DELETE(p)	{ if(p){(p)->Release(); delete (p); (p)=nullptr;} }

//-----------------------------------------------------------------------------

ZRenderDevice::ZRenderDevice()
	: m_pWindow(nullptr)
	, m_pFactory(nullptr)
	, m_pDevice(nullptr)
	, m_featureLevel(D3D_FEATURE_LEVEL_11_0)
{

}

ZRenderDevice::~ZRenderDevice()
{

}

bool ZRenderDevice::Init(ZAppWindow* pWindow)
{
	m_pWindow = pWindow;

	if (!InitDXGIFactory())
	{
		return false;
	}

	if (!InitDeviceCaps())
	{
		return false;
	}

	if (!InitDevice())
	{
		return false;
	}

	if (!InitSwapChain())
	{
		return false;
	}

	return true;
}

void ZRenderDevice::Uninit()
{
	UninitSwapChain();
	UninitDevice();
	UninitDeviceCaps();
	UninitDXGIFactory();
}

const ZAppWindow* ZRenderDevice::GetWindow() const
{
	return m_pWindow;
}

IDXGIFactory* ZRenderDevice::GetDXGIFactory() const
{
	return m_pFactory;
}

ID3D11Device* ZRenderDevice::GetD3DDevice() const
{
	return m_pDevice;
}

bool ZRenderDevice::InitDevice()
{
	D3D_FEATURE_LEVEL maxSupportedFeatureLevel = D3D_FEATURE_LEVEL_9_1;
	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};

	HRESULT hr = D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		&featureLevels[0],
		ARRAYSIZE(featureLevels),
		D3D11_SDK_VERSION,
		nullptr,
		&maxSupportedFeatureLevel,
		nullptr
	);

	if (FAILED(hr))
	{
		ZTRACE_MSSAGE("renderdeviced3d", "failed to enumerate feature level");
		return false;
	}

	//ZTRACE_MSSAGE("renderdeviced3d, using feature level" + maxSupportedFeatureLevel);

	hr = D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		featureLevels,
		ARRAYSIZE(featureLevels),
		D3D11_SDK_VERSION,
		&m_pDevice,
		&maxSupportedFeatureLevel,
		nullptr
	);

	if (FAILED(hr))
	{
		ZTRACE_MSSAGE("renderdeviced3d", "failed to create device");
		return false;
	}

	ZTRACE_MSSAGE("renderdeviced3d", "create device successful");

	return true;
}

void ZRenderDevice::UninitDevice()
{
	m_pDevice->Release();
	m_pDevice = nullptr;
}

bool ZRenderDevice::InitSwapChain()
{
	return m_swapChain.Init(this);
}

void ZRenderDevice::UninitSwapChain()
{
	m_swapChain.Uninit();
}

bool ZRenderDevice::InitDXGIFactory()
{
	HRESULT result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&m_pFactory);
	if (FAILED(result))
	{
		return false;
	}
	return true;
}

void ZRenderDevice::UninitDXGIFactory()
{
	// Release the factory.
	m_pFactory->Release();
	m_pFactory = nullptr;
}

bool ZRenderDevice::InitDeviceCaps()
{
	IDXGIAdapter* pAdapter = nullptr;
	HRESULT result = m_pFactory->EnumAdapters(0, &pAdapter);
	if (FAILED(result))
	{
		return false;
	}

	IDXGIOutput* pAdapterOutput = nullptr;
	result = pAdapter->EnumOutputs(0, &pAdapterOutput);
	if (FAILED(result))
	{
		return false;
	}

	uint32 nNumModes = 0;
	result = pAdapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &nNumModes, nullptr);
	if (FAILED(result))
	{
		return false;
	}

	DXGI_MODE_DESC* pDisplayModeList = new DXGI_MODE_DESC[nNumModes];
	if (!pDisplayModeList)
	{
		return false;
	}

	result = pAdapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &nNumModes, pDisplayModeList);
	if (FAILED(result))
	{
		return false;
	}

	for (uint32 i = 0; i < nNumModes; i++)
	{
		SDisplayDesc& desc = m_deviceCaps.m_aSupportedDisplays.push_back();
		desc.m_nWidth = pDisplayModeList[i].Width;
		desc.m_nHeight = pDisplayModeList[i].Height;

		desc.m_nRefreshRateNumerator = pDisplayModeList[i].RefreshRate.Numerator;
		desc.m_nRefreshRateDenominator = pDisplayModeList[i].RefreshRate.Denominator;
	}

	// Get the adapter (video card) description.
	DXGI_ADAPTER_DESC adapterDesc;
	result = pAdapter->GetDesc(&adapterDesc);
	if (FAILED(result))
	{
		return false;
	}

	// Store the dedicated video card memory in megabytes.
	m_deviceCaps.m_nMaxGpuMem = adapterDesc.DedicatedVideoMemory;
	m_deviceCaps.m_sAdapterDescription = adapterDesc.Description;

	// Release the display mode list.
	delete[] pDisplayModeList;
	pDisplayModeList = nullptr;

	// Release the adapter output.
	pAdapterOutput->Release();
	pAdapterOutput = nullptr;

	// Release the adapter.
	pAdapter->Release();
	pAdapter = nullptr;

	return true;
}

void ZRenderDevice::UninitDeviceCaps()
{

}
