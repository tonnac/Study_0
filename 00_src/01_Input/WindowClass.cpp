#include "WindowClass.h"

Window * g_pWindow = nullptr;
HWND g_hWnd;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	LRESULT ret;
	if (ret = g_pWindow->MsgProc(hwnd, msg, wparam, lparam))
	{
		return ret;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}
Window::Window()
{
	g_pWindow = this;
}

bool Window::setWindow(HINSTANCE hinst)
{
	WNDCLASSEX wd;
	ZeroMemory(&wd, sizeof(WNDCLASSEX));
	wd.cbSize = sizeof(WNDCLASSEX);
	wd.style = CS_VREDRAW | CS_HREDRAW;
	wd.lpfnWndProc = WndProc;
	wd.hInstance = hinst;
	wd.hIcon = LoadIcon(nullptr, IDI_SHIELD);
	wd.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wd.lpszMenuName = L"Window";
	wd.lpszClassName = L"Class";
	wd.hIconSm = LoadIcon(nullptr, IDI_ERROR);

	if (!RegisterClassEx(&wd))
	{
		return false;
	}

	m_hWnd = CreateWindowEx(WS_EX_APPWINDOW,
		wd.lpszClassName,
		wd.lpszMenuName,
		WS_OVERLAPPEDWINDOW,
		0,
		0,
		1024,
		768,
		nullptr,
		nullptr,
		wd.hInstance,
		nullptr);
	
	if (m_hWnd == nullptr)
	{
		return false;
	}
	::g_hWnd = m_hWnd;

	GetClientRect(m_hWnd, &m_rtClient);
	GetWindowRect(m_hWnd, &m_rtWindow);

	CenterWindow();

	ShowWindow(m_hWnd, SW_SHOW);
	return true;
}
bool Window::Run()
{
	if (!GameInit()) return false;
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
				break;
			MsgEvent(msg);
		}
		else
		{
			Sleep(1);
			GameRun();
		}
	}
	return GameRelease();
}
LRESULT CALLBACK Window::MsgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return 0;
}
bool Window::GameInit()
{
	return true;
}
bool Window::GameRun()
{
	return true;
}
bool Window::GameRelease()
{
	return true;
}
void Window::CenterWindow()
{
	int iScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
	int iScreenHeight = GetSystemMetrics(SM_CYFULLSCREEN);
	int x = ((iScreenWidth - (m_rtWindow.right - m_rtWindow.left)) / 2);
	int y = ((iScreenHeight - (m_rtWindow.bottom - m_rtWindow.top)) / 2);
	MoveWindow(m_hWnd, x, y, m_rtWindow.right - m_rtWindow.left, m_rtWindow.bottom, m_rtWindow.top);
}
void Window::MsgEvent(MSG msg)
{
	I_input.MsgEvent(msg);
}