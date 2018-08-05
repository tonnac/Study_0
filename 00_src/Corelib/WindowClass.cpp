#include "WindowClass.h"

KWindow *	g_pWindow = nullptr;
HWND		g_hWnd = nullptr;
HINSTANCE	g_hInstance = nullptr;

LRESULT	CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	assert(g_pWindow != nullptr);

	LRESULT Ret;
	if (Ret = g_pWindow->MsgProc(hwnd, msg, wparam, lparam))
	{
		return Ret;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

KWindow::KWindow()
{
	g_pWindow = this;
}
RECT KWindow::getrtClient()
{
	return m_rtClient;
}
bool KWindow::SetWindow(HINSTANCE hInst)
{
	ZeroMemory(&m_wdClass, sizeof(WNDCLASSEX));
	m_wdClass.cbSize = sizeof(WNDCLASSEX);
	m_wdClass.style = CS_HREDRAW | CS_VREDRAW;
	m_wdClass.lpfnWndProc = WndProc;
	m_wdClass.hInstance = m_hInstance = hInst;
	m_wdClass.hIcon = LoadIcon(nullptr, IDI_SHIELD);
	m_wdClass.hCursor = LoadCursor(nullptr, IDC_NO);
	m_wdClass.lpszMenuName = L"NewWindow";
	m_wdClass.lpszClassName = L"ClassName";
	m_wdClass.hIconSm = LoadIcon(nullptr, IDI_EXCLAMATION);
	if (!RegisterClassEx(&m_wdClass))
	{
		return false;
	}
	m_hWnd = CreateWindowEx(WS_EX_APPWINDOW,
		m_wdClass.lpszClassName,
		m_wdClass.lpszMenuName,
		WS_OVERLAPPEDWINDOW,
		0,
		0,
		1024,
		768,
		nullptr,
		nullptr,
		m_wdClass.hInstance,
		nullptr);
	if (m_hWnd == nullptr)
	{
		return false;
	}
	g_hWnd = m_hWnd;
	GetClientRect(m_hWnd, &m_rtClient);
	GetWindowRect(m_hWnd, &m_rtWindow);
	CenterWindow();
	return true;
}
bool KWindow::Run()
{
	if (!GameInit())
	{
		return false;
	}
	ShowWindow(m_hWnd, SW_SHOW);
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			I_KInput.MsgEvent(msg);
		}
		else
		{
			GameFrame();
			GameRender();
		}
	}
	return GameRelease();
}
bool KWindow::GameInit()
{
	return true;
}
bool KWindow::GameFrame()
{
	return true;
}
bool KWindow::GameRender()
{
	return true;
}
bool KWindow::GameRelease()
{
	return true;
}
LRESULT	CALLBACK KWindow::MsgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return 0;
}
void KWindow::CenterWindow()
{
	int iScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
	int iScreenHeight = GetSystemMetrics(SM_CYFULLSCREEN);
	int x = ((iScreenWidth - (m_rtWindow.right - m_rtWindow.left)) / 2);
	int y = ((iScreenHeight - (m_rtWindow.bottom - m_rtWindow.top)) / 2);
	MoveWindow(m_hWnd, x, y, m_rtWindow.right - m_rtWindow.left, m_rtWindow.bottom - m_rtWindow.top, true);
}
bool KWindow::Init()
{
	return true;
}
bool KWindow::Frame()
{
	return true;
}
bool KWindow::Render()
{
	return true;
}
bool KWindow::Release()
{
	return true;
}
