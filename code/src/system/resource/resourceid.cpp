#include "resourceid.h"
#include "system/base/types.h"

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

uint64 ZResourceId::Hash() const
{
	return ZStringHash()(m_rid);
}

const ZString& ZResourceId::ToString() const
{
	return m_rid;
}
