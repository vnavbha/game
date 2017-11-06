#pragma once

#include "system/base/build_system_base.h"
#include "system/base/types.h"

//-----------------------------------------------------------------------------

class SYSTEM_BASE_API ZFilePath final
{
public:
	ZFilePath();
	ZFilePath(const ZString& sPath);
	~ZFilePath();

	ZFilePath& operator+= (const ZFilePath& path);
	ZFilePath operator+ (const ZFilePath& path) const;
	ZFilePath& operator+= (const ZString& sPath);
	ZFilePath operator+ (const ZString& sPath) const;	

	bool IsValid() const;
	const ZString& GetDrive() const;
	const ZString& GetFileName() const;
	const ZString& GetExtension() const;
	const ZString& GetDirectory() const;
	ZString ToFullPath() const;

	static ZString PathSeparator();

private:
	static ZString s_sPathSeparator;

	ZString m_sDrive;
	ZString m_sFileName;
	ZString m_sExtension;
	ZString m_sDirectory;
	bool m_bIsValid;
};
