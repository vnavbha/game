#pragma once

#include "system/base/build_system_base.h"
#include "iinputstream.h"
#include <fstream>

//-----------------------------------------------------------------------------

class SYSTEM_BASE_API ZInputFileStream : public IInputStream
{
public:
	ZInputFileStream();
	virtual ~ZInputFileStream();

	bool Open(const ZFilePath &path) override;
	void Close() override;
	
	size_t Read(char* pDestination, uint64 nSize) override;
	size_t ReadLine(ZString& sResult) override;
	bool IsEof() const;

protected:
	std::ifstream m_stream;
};