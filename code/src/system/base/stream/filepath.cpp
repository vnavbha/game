#include "filepath.h"
#include "system/base/eastlextend.h"
#include "system/base/debug/debug.h"

//-----------------------------------------------------------------------------

ZString ZFilePath::s_sPathSeparator = "/";

//-----------------------------------------------------------------------------

ZFilePath::ZFilePath()
	: m_bIsValid(false)
{

}

ZFilePath::ZFilePath(const ZString& sPath)
	: m_bIsValid(false)
{
	char fullPath[MAX_PATH];
	_fullpath(fullPath, sPath.c_str(), MAX_PATH);

	ZString sPathNormalized = fullPath;
	replace_all(sPathNormalized, ZString("\\"), PathSeparator());
	ZString sDummy;
	if (!split_first(sPathNormalized, m_sDrive, sDummy, ZString(":")))
	{
		m_sDrive = "";
	}
	
	ZString sPathSeparator = ZString() + PathSeparator();
	if (!split_last(sPathNormalized, sDummy, m_sExtension, ZString(".")))
	{
		// directory
		m_sDirectory = sPath;
	}
	else if(!split_last(sPathNormalized, m_sDirectory, m_sFileName, sPathSeparator))
	{
		return;
	}
	
	m_bIsValid = true;
}

ZFilePath::~ZFilePath()
{

}

//-----------------------------------------------------------------------------

ZFilePath& ZFilePath::operator+=(const ZFilePath& path)
{
	*this = *this + path.ToFullPath();
	return *this;
}

ZFilePath ZFilePath::operator+(const ZFilePath& path) const
{
	return *this + path.ToFullPath();
}

ZFilePath& ZFilePath::operator+=(const ZString& sPath)
{
	*this = *this + sPath;
	return *this;
}

ZFilePath ZFilePath::operator+(const ZString& sPath) const
{
	return ZFilePath(ToFullPath() + PathSeparator() + sPath);
}

bool ZFilePath::IsValid() const
{
	return m_bIsValid;
}
const ZString& ZFilePath::GetDrive() const
{
	ZASSERT(IsValid());
	return m_sDrive;
}

const ZString& ZFilePath::GetFileName() const
{
	ZASSERT(IsValid());
	return m_sFileName;
}

const ZString& ZFilePath::GetExtension() const
{
	ZASSERT(IsValid());
	return m_sExtension;
}

const ZString& ZFilePath::GetDirectory() const
{
	ZASSERT(IsValid());
	return m_sDirectory;
}

ZString ZFilePath::PathSeparator()
{
	return s_sPathSeparator;
}

ZString ZFilePath::ToFullPath() const
{
	ZASSERT(IsValid());
	return m_sDirectory + s_sPathSeparator + m_sFileName;
}