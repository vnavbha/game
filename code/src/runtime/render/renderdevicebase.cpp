#include "renderdevicebase.h"
#include "system/base/debug/debug.h"

//-----------------------------------------------------------------------------

ZRenderDeviceBase::ZRenderDeviceBase()
{

}

ZRenderDeviceBase::~ZRenderDeviceBase()
{

}

//-----------------------------------------------------------------------------

const SDeviceCaps& ZRenderDeviceBase::GetDeviceCaps() const
{
	return m_deviceCaps;
}
