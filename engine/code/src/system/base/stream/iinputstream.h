#pragma once

#include "istream.h"

//-----------------------------------------------------------------------------

class IInputStream : public IStream
{
	virtual bool Read(char* pDestination, uint64 nSize) = 0;
	virtual bool ReadLine(ZString& sResult) = 0;
};
