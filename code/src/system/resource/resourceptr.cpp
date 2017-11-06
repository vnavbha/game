#include "resourceptr.h"

//-----------------------------------------------------------------------------

ZResourcePtr::ZResourcePtr()
	: m_pData(nullptr)
{

}

ZResourcePtr::ZResourcePtr(TSharedPtr<const ZResourceData> pData)
	: m_pData(pData)
{

}

ZResourcePtr::~ZResourcePtr()
{

}

//-----------------------------------------------------------------------------

const ZResourceData* ZResourcePtr::GetResourceData() const
{
	return m_pData.get();
}

bool ZResourcePtr::IsNull() const
{
	return m_pData == nullptr;
}
