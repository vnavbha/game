#include "appwindow.h"
#include "system/base/debug/debug.h"

//-----------------------------------------------------------------------------

ZAppWindow::ZAppWindow()
	: m_instance(nullptr)
	, m_handle(nullptr)
	, m_nWidth(800)
	, m_nHeight(600)
	, m_bFullScreen(false)
{

}

ZAppWindow::~ZAppWindow()
{

}

bool ZAppWindow::Init()
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	DEVMODE dmScreenSettings;
	int posX, posY;

	// Get the instance of this application.
	m_instance = GetModuleHandle(nullptr);

	m_sWindowClass = L"Engine";

	// Setup the windows class with default settings.
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = HandleMessage;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_instance;
	wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = m_sWindowClass.c_str();
	wc.cbSize = sizeof(WNDCLASSEX);

	// Register the window class.
	RegisterClassEx(&wc);

	// Determine the resolution of the clients desktop screen.
	m_nHeight = GetSystemMetrics(SM_CXSCREEN);
	m_nWidth = GetSystemMetrics(SM_CYSCREEN);

	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	if (m_bFullScreen)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)m_nHeight;
		dmScreenSettings.dmPelsHeight = (unsigned long)m_nWidth;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;
	}
	else
	{
		// If windowed then set it to 800x600 resolution.
		m_nWidth = 800;
		m_nHeight = 600;

		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - m_nWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - m_nHeight) / 2;
	}

	// Create the window with the screen settings and get the handle to it.
	m_handle = CreateWindowEx(WS_EX_APPWINDOW, m_sWindowClass.c_str(), m_sWindowClass.c_str(),
		WS_OVERLAPPEDWINDOW,
		posX, posY, m_nWidth, m_nHeight, nullptr, nullptr, m_instance, nullptr);

	if (m_handle == nullptr)
	{
		ZTRACE_MESSAGE("appwindow", "Create window error %lu", GetLastError());
		return false;
	}

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(m_handle, SW_SHOW);
	SetForegroundWindow(m_handle);
	SetFocus(m_handle);

	// Hide the mouse cursor.
	ShowCursor(false);

	return ZAppWindowBase::Init();
}

void ZAppWindow::Uninit()
{
	ShowCursor(true);

	// Fix the display settings if leaving full screen mode.
	if (m_bFullScreen)
	{
		ChangeDisplaySettings(nullptr, 0);
	}

	// Remove the window.
	DestroyWindow(m_handle);
	m_handle = nullptr;

	// Remove the application instance.
	UnregisterClass(m_sWindowClass.c_str(), m_instance);
	m_instance = nullptr;

	ZAppWindowBase::Uninit();
}

bool ZAppWindow::Update(const SGameTime& gameTime)
{
	// Loop until there is a quit message from the window or the user.
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	// Handle the windows messages.
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// If windows signals to end the application then exit out.
	if (msg.message == WM_QUIT)
	{
		return false;
	}
	else
	{
		return true;
	}

	ZAppWindowBase::Update(gameTime);
}

//-----------------------------------------------------------------------------

uint32 ZAppWindow::GetHeight() const
{
	return m_nHeight;
}

uint32 ZAppWindow::GetWidth() const
{
	return m_nWidth;
}

HWND ZAppWindow::GetHandle() const
{
	return m_handle;
}

bool ZAppWindow::IsFullScreen() const
{
	return m_bFullScreen;
}

LRESULT ZAppWindow::HandleMessage(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
		// Check if the window is being destroyed.
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		// Check if the window is being closed.
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}

		default:
		{
			return DefWindowProc(hwnd, umessage, wparam, lparam);
		}
	}
}
