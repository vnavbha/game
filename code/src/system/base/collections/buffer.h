#pragma once

#include "system/base/build_system_base.h"
#include "system/base/types.h"

//-----------------------------------------------------------------------------

class SYSTEM_BASE_API ZBuffer
{
public:
	ZBuffer();
	ZBuffer(size_t nSize);
	virtual ~ZBuffer();

	ZBuffer(ZBuffer&& value);
	ZBuffer& operator=(ZBuffer&& value);

	ZBuffer(TArray<char>&& value);
	ZBuffer& operator=(TArray<char>&& value);

	ZBuffer& operator+=(const TArray<char>& value);
	ZBuffer& operator+=(const ZBuffer& buffer);

	const char* Data() const;

	void Clear();
	void Reserve(size_t nSize);	
	size_t Size() const;

private:
	TArray<char> m_aData;
};
