#pragma once
#include "../appwindowbase.h"
#include "system/base/types.h"
#include <Windows.h>
#include <functional>

//-----------------------------------------------------------------------------

class SYSTEM_BASE_API ZAppWindow : public ZAppWindowBase
{
public:
	ZAppWindow();
	virtual ~ZAppWindow();
	
	bool Init() override;
	void Uninit() override;
	bool Update(const STime& time);

	uint32 GetHeight() const;
	uint32 GetWidth() const;
	HWND GetHandle() const;
	bool IsFullScreen() const;
	
	static LRESULT CALLBACK HandleMessage(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);

private:

	HINSTANCE m_instance;
	HWND m_handle;
	uint32 m_nWidth;
	uint32 m_nHeight;
	bool m_bFullScreen;

	ZWString m_sWindowClass;
};