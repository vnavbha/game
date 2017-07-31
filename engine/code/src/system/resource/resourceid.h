#pragma once

#include "system/base/types.h"

//-----------------------------------------------------------------------------

class ZResourceId
{
public:
	ZResourceId(const ZString& sRid);
	~ZResourceId();

	bool IsValid() const;
	const ZString& ToString() const;
	void FromString(const ZString sRid);

	ZString ToFilePath() const;

private:
	ZString ProtocolToPath(const ZString sProtocol) const;
	ZString m_rid;
};
