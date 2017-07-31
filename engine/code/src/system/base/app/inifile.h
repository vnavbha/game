#pragma once

#include "system/base/types.h"

class IInputStream;
class ZFilePath;

//-----------------------------------------------------------------------------

class ZIniFile final
{
public:
	ZIniFile();
	~ZIniFile();

	void Init(const ZFilePath& path);
	ZString GetOption(const ZString& sKey) const;

private:
	IInputStream* m_pStream;

	THashMap<ZString, ZString> m_aValues;
};
