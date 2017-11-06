#pragma once
#include "build_system_resource.h"

#include "system/resource/resourceptr.h"
#include "system/resource/resourcedata.h"

#include "system/base/subsystem/subsystem.h"
#include "system/base/stream/filepath.h"
#include "system/base/types.h"

class ZResourceId;

#define READ_BUFFER_SIZE 1024*2

//-----------------------------------------------------------------------------

class SYSTEM_RESOURCE_API ZSystemResourceSubSystem : public ZSubSystem
{
public:
	ZSystemResourceSubSystem();
	virtual ~ZSystemResourceSubSystem();

	bool Init() override;
	void Uninit() override;
	void Update(const STime& time) override;

	ZResourcePtr Load(const ZResourceId& rid);

protected:	
	ZFilePath ToFilePath(const ZResourceId& rid) const;
	ZResourcePtr Get(const ZResourceId& rid);

protected:
	ZFilePath m_resourcePath;
	THashMap< uint64, TSharedPtr<ZResourceData> > m_aResources;
};
