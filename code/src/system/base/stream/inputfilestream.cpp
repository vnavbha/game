#include "inputfilestream.h"
#include "filepath.h"
#include <string>

//-----------------------------------------------------------------------------

ZInputFileStream::ZInputFileStream()
{
}

ZInputFileStream::~ZInputFileStream()
{
	Close();
}

bool ZInputFileStream::Open(const ZFilePath& path)
{
	if (path.IsValid() == false)
	{
		return false;
	}

	m_stream.open(path.ToFullPath().c_str(), std::ifstream::in);
	if (m_stream.fail())
	{
		return false;
	}
	return true;
}

void ZInputFileStream::Close()
{
	m_stream.close();
}

size_t ZInputFileStream::Read(char* pDestination, uint64 nSize)
{
	m_stream.read(pDestination, nSize);
	return m_stream.gcount();
}

size_t ZInputFileStream::ReadLine(ZString& sResult)
{
	std::string str;
	std::getline(m_stream, str);
	sResult = str.c_str();	
	return str.length();
}

bool ZInputFileStream::IsEof() const
{
	if (m_stream.fail() || m_stream.eof())
	{
		return true;
	}
	return false;
}
