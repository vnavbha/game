#pragma once

#include "istream.h"

//-----------------------------------------------------------------------------

class IInputStream : public IStream
{
	virtual size_t Read(char* pDestination, uint64 nSize) = 0;
	virtual size_t ReadLine(ZString& sResult) = 0;
};
