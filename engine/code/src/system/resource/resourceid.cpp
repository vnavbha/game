#include "resourceid.h"

ZResourceId::ZResourceId(const ZString& sRid)
{
	m_rid = sRid;
}

ZResourceId::~ZResourceId()
{

}

bool ZResourceId::IsValid() const
{
	return m_rid.empty() == false;
}

const ZString& ZResourceId::ToString() const
{
	return m_rid;
}

void ZResourceId::FromString(const ZString sRid)
{
	m_rid = sRid;
}

ZString ZResourceId::ToFilePath() const
{
	if (IsValid() == false)
	{
		return ZString();
	}

	size_t iProtocol = m_rid.find(':');
	if (iProtocol == ZString::npos)
	{
		return ZString();
	}
	ZString sProtocol = m_rid.substr(0, iProtocol);
 	ZString sPath = m_rid.substr(iProtocol, m_rid.length());

	return ProtocolToPath(sProtocol) + sPath;
}

