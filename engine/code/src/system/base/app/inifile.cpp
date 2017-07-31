#include "inifile.h"
#include "system/base/debug/debug.h"
#include "system/base/memory/memory.h"
#include "system/base/stream/inputfilestream.h"
#include "system/base/stream/filepath.h"
#include "system/base/eastlextend.h"

//-----------------------------------------------------------------------------

ZIniFile::ZIniFile()
{

}

ZIniFile::~ZIniFile()
{

}

void ZIniFile::Init(const ZFilePath& path)
{
	ZASSERT(path.IsValid());
	ZInputFileStream stream;
	if (stream.Open(path.ToFullPath()) == false)
	{
		ZTRACE_MESSAGE("inifile", "failed to open %s", path.ToFullPath());
		return;
	}

	ZString sLine;
	while (stream.ReadLine(sLine))
	{
		ZString sLeft, sRight;
		if (split_first(sLine, sLeft, sRight, ZString("=")) == false)
		{
			ZTRACE_MESSAGE("inifile", "Invalid option", sLine);
		}
		
		m_aValues.insert(TPair<ZString, ZString>(sLeft, sRight));
	}
}

ZString ZIniFile::GetOption(const ZString& sKey) const
{
	auto it = m_aValues.find(sKey);
	if (it == m_aValues.end())
	{
		return ZString();
	}

	return it->second;
}
