#pragma once

#include "iinputstream.h"
#include <fstream>

//-----------------------------------------------------------------------------

class ZInputFileStream : public IInputStream
{
public:
	ZInputFileStream();
	virtual ~ZInputFileStream();

	bool Open(const ZFilePath &path) override;
	void Close() override;
	bool Read(char* pDestination, uint64 nSize) override;
	bool ReadLine(ZString& sResult) override;

protected:
	std::ifstream m_stream;
};