#pragma once

#include "system/base/build_system_base.h"
#include "system/base/stream/filepath.h"
#include "system/base/app/inifile.h"
#include "system/base/subsystem/subsystems.h"
#include "system/base/memory/memory.h"
#include "system/base/debug/debug.h"

//-----------------------------------------------------------------------------

class ZSubSystem;
class ZAppWindow;

//-----------------------------------------------------------------------------

class SYSTEM_BASE_API ZAppBase
{
public:
	ZAppBase();
	virtual ~ZAppBase();

	virtual void Init();
	virtual void Uninit();
	virtual void Run();

	virtual bool Update();

	template<typename T>
	T* GetSubSystem(ESubSystems id) const;

	template <class T>
	T GetApplicationOption(const ZString& sKey, const T& valDefault = T());

	ZAppWindow* GetWindow() const;
	const ZFilePath GetExePath() const;

	template<typename T>
	bool RegisterSubSystem(ESubSystems id);
	void UnregisterSubSystem(ESubSystems id);

protected:

	TFixedArray<ZSubSystem*, SS_MAX> m_aSubSystems;
	
	ZAppWindow* m_pWindow;
	ZFilePath m_exePath;
	ZIniFile m_iniFile;
};

#define REGISTER_SUBSYSTEM(type, id) RegisterSubSystem<type>(id)
#define UNREGISTER_SUBSYSTEM(type, id) UnregisterSubSystem(id)

//-----------------------------------------------------------------------------

template<typename T>
T* ZAppBase::GetSubSystem(ESubSystems id) const
{
	return static_cast<T*>(m_aSubSystems[id]);
}

template <>
inline ZString ZAppBase::GetApplicationOption(const ZString& sKey, const ZString& valDefault)
{
	ZString sOption = m_iniFile.GetOption(sKey);
	if (sOption.empty())
	{
		return valDefault;
	}
	return sOption;
}

template <>
inline int32 ZAppBase::GetApplicationOption(const ZString& sKey, const int32& valDefault)
{
	ZString sOption = m_iniFile.GetOption(sKey);
	if (sOption.empty())
	{
		return valDefault;
	}

	return ZFnToInt(sOption.c_str());
}

template <>
inline bool ZAppBase::GetApplicationOption(const ZString& sKey, const bool& valDefault)
{
	ZString sOption = m_iniFile.GetOption(sKey);
	if (sOption.empty())
	{
		return valDefault;
	}

	if (ZFnICmp(sOption.c_str(), "true"))
	{
		return true;
	}
	if (ZFnICmp(sOption.c_str(), "false"))
	{
		return false;
	}

	int32 nValue = ZFnToInt(sOption.c_str());
	if (nValue == 1)
	{
		return true;
	}
	return false;
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

extern SYSTEM_BASE_API ZAppBase* GetApp();
extern SYSTEM_BASE_API void  SetApp(ZAppBase* pApp);
