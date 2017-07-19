#pragma once

#include "system/base/types.h"

class ZAppWindow;

//-----------------------------------------------------------------------------

struct SDisplayDesc
{
	uint32 m_nWidth;
	uint32 m_nHeight;
	uint32 m_nRefreshRateNumerator;
	uint32 m_nRefreshRateDenominator;
};

struct SDeviceCaps
{
	size_t m_nMaxGpuMem;
	TArray<SDisplayDesc> m_aSupportedDisplays;
	ZWString m_sAdapterDescription;
};

//-----------------------------------------------------------------------------

class ZRenderDeviceBase
{
public:
	ZRenderDeviceBase();
	virtual ~ZRenderDeviceBase();

	virtual bool Init(ZAppWindow* pWindow) = 0;
	virtual void Uninit() = 0;

	const SDeviceCaps& GetDeviceCaps() const;		 

protected:
	SDeviceCaps m_deviceCaps;
};
