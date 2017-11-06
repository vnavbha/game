#include "buffer.h"

//-----------------------------------------------------------------------------

ZBuffer::ZBuffer()
{

}

ZBuffer::ZBuffer(size_t nSize)
{
	Reserve(nSize);
}

ZBuffer::ZBuffer(ZBuffer&& value)
{
	m_aData = std::move(value.m_aData);
}

ZBuffer::ZBuffer(TArray<char>&& value)
{
	m_aData = std::forward< TArray<char> >(value);
}

ZBuffer& ZBuffer::operator=(TArray<char>&& value)
{
	m_aData = std::forward< TArray<char> >(value);
	return *this;
}

ZBuffer& ZBuffer::operator=(ZBuffer&& value)
{
	m_aData = std::move(value.m_aData);
	return *this;
}

ZBuffer::~ZBuffer()
{

}

//-----------------------------------------------------------------------------

ZBuffer& ZBuffer::operator+=(const TArray<char>& value)
{
	Reserve(Size() + value.size());
	m_aData.insert(m_aData.end(), value.begin(), value.begin() + value.size());
	return *this;
}

ZBuffer& ZBuffer::operator+=(const ZBuffer& buffer)
{
	Reserve(Size() + buffer.Size());
	m_aData.insert(m_aData.end(), buffer.m_aData.begin(), buffer.m_aData.begin() + buffer.m_aData.size());
	return *this;
}

size_t ZBuffer::Size() const
{
	return m_aData.size();
}

const char* ZBuffer::Data() const
{
	return m_aData.data();
}

void ZBuffer::Clear()
{
	m_aData.clear();
}

void ZBuffer::Reserve(size_t nSize)
{
	m_aData.reserve(nSize);
}
