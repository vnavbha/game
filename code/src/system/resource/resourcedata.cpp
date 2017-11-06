#include "resourcedata.h"

//-----------------------------------------------------------------------------

ZResourceData::ZResourceData(ZBuffer&& data)
{
	m_data = std::move(data);
}

ZResourceData::ZResourceData(ZResourceData&& data)
{
	m_data = std::move(data.m_data);
}

ZResourceData& ZResourceData::operator=(ZResourceData&& data)
{
	m_data = std::move(data.m_data);
	return *this;
}

ZResourceData::~ZResourceData()
{

}

//-----------------------------------------------------------------------------

const ZBuffer& ZResourceData::GetData() const
{
	return m_data;
}

//-----------------------------------------------------------------------------
