#include "engineapp.h"
#include "system/base/memory/memory.h"
#include "system/base/memory/dlmalloc.h"
#include <Windows.h>

//-----------------------------------------------------------------------------

int main()
{
	ZAppBase* pApp = ZNEW ZEngineApp();
	SetApp(pApp);

	pApp->Init();
	pApp->Run();
	pApp->Uninit();
	 
	ZDELETE(pApp);
	SetApp(nullptr);	
	return 0;
}
