#pragma once

#include "appwindow.h"
#include "system/base/subsystem/subsystems.h"
#include "system/base/memory/memory.h"
#include "system/base/debug/debug.h"

//-----------------------------------------------------------------------------

class ZAppWindow;
class ZSubSystem;

//-----------------------------------------------------------------------------

class ZAppBase
{
public:
	ZAppBase();
	virtual ~ZAppBase();

	virtual void Init();
	virtual void Uninit();
	virtual void Run();

	virtual bool Update();

	ZAppWindow* GetWindow() const;

	template<typename T>
	T* GetSubSystem(ESubSystems id) const;

	template<typename T>
	bool RegisterSubSystem(ESubSystems id);
	void UnregisterSubSystem(ESubSystems id);

protected:
	ZAppWindow* m_pWindow;
	TFixedArray<ZSubSystem*, SS_MAX> m_aSubSystems;
};

#define REGISTER_SUBSYSTEM(type, id) RegisterSubSystem<type>(id)
#define UNREGISTER_SUBSYSTEM(type, id) UnregisterSubSystem(id)

//-----------------------------------------------------------------------------

template<typename T>
T* ZAppBase::GetSubSystem(ESubSystems id) const
{
	return static_cast<T*>(m_aSubSystems[id]);
}

template<typename T>
bool ZAppBase::RegisterSubSystem(ESubSystems id)
{
	ZSubSystem* pSubSystem = ZNEW T();
	if (!pSubSystem->Init())
	{
		ZBREAK();
		return false;
	}
	m_aSubSystems[id] = pSubSystem;
	return true;
}

//-----------------------------------------------------------------------------

extern ZAppBase* GetApp();
extern void SetApp(ZAppBase* pApp);
