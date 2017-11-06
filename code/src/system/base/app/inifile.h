#pragma once

#include "../build_system_base.h"
#include "system/base/types.h"

class IInputStream;
class ZFilePath;

//-----------------------------------------------------------------------------

class SYSTEM_BASE_API ZIniFile final
{
public:
	ZIniFile();
	~ZIniFile();

	void ParseOptions(const ZFilePath& path);
	ZString GetOption(const ZString& sKey) const;

private:
	IInputStream* m_pStream;

	THashMap<ZString, ZString> m_aValues;
};
