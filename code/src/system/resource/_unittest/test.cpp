
#include "stdafx.h"
#include "CppUnitTest.h"

#ifdef WINDOWS
#include <windows.h>
#include <string>
#endif

#include "system/base/app/appbase.h"
#include "system/resource/resourceid.h"
#include "system/resource/system.resource.h"

EXTERN_C IMAGE_DOS_HEADER __ImageBase;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

class ZTestApp : public ZAppBase
{
public:
	virtual void Init() override
	{
		WCHAR pStr[MAX_PATH] = { 0 };
		GetModuleFileNameW((HINSTANCE)&__ImageBase, pStr, _countof(pStr));
		m_exePath = ZFilePath(ZString().assign_convert(pStr));
		ZAppBase::Init();
		REGISTER_SUBSYSTEM(ZSystemResourceSubSystem, SS_SYSTEM_RESOURCE);
	}

	virtual void Uninit() override
	{
		UNREGISTER_SUBSYSTEM(ZSystemResourceSubSystem, SS_SYSTEM_RESOURCE);
		ZAppBase::Uninit();
	}
};

namespace UnitTest 
{		
	TEST_CLASS(system_resource)
	{
	public:
		
		TEST_METHOD(ResourceId)
		{
			ZTestApp* pApp = ZNEW ZTestApp();
			SetApp(pApp);
			pApp->Init();
			ZResourceId rid("data:_test/data.dat");

			ZSystemResourceSubSystem* pResourceSystem = pApp->GetSubSystem<ZSystemResourceSubSystem>(SS_SYSTEM_RESOURCE);
			ZResourcePtr ptr = pResourceSystem->Load(rid);

			Assert::IsTrue(ptr.IsNull() == false);

			ZString str(ptr.GetResourceData()->GetData().Data());
			Assert::IsTrue(str == "test data");
			pApp->Uninit();
		}
	};
}