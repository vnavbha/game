#pragma once

#include "system/base/types.h"

class ZFilePath;

//-----------------------------------------------------------------------------

class IStream
{
public:
	virtual bool Open(const ZFilePath& sPath) = 0;
	virtual void Close() = 0;
};
