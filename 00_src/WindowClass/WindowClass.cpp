#include "WindowClass.h"

Window * g_pWindow = nullptr;

bool Window::SetWindow(HINSTANCE hinst, const TCHAR * pTitieName,
	UINT iWidth, UINT iHeight)
{
	m_hInstance = hinst;
	WNDCLASSEX wc;							 
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;		 
	wc.lpfnWndProc = WndProc;				 
	wc.hInstance = m_hInstance;				
	wc.lpszClassName = L"Window";
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	if (RegisterClassEx(&wc) == false)	 
	{
		return false;
	}

	m_hWnd = CreateWindowEx(
		WS_EX_APPWINDOW,
		L"Window",
		pTitieName,
		m_dwStyle,
		0, 
		0, 
		iWidth,
		iHeight,
		nullptr,
		nullptr,
		m_hInstance,
		nullptr);
	if (m_hWnd == nullptr)
	{
		return false;
	}
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
			{
				break;
			}
		}
		else
		{
			GameRun();
		}
	}
	return GameRelease();
}

void Window::Set(DWORD m_dwStyle)
{
	this->m_dwStyle = m_dwStyle;
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
Window::Window()
{
	m_dwStyle = WS_OVERLAPPEDWINDOW;
	g_pWindow = this;
}
Window::~Window()
{
}

void Window::CenterWindow()
{
	int iScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
	int iScreenHeight = GetSystemMetrics(SM_CYFULLSCREEN);
	int x = (iScreenWidth - (m_rtWindow.right - m_rtWindow.left)) / 2;
	int y = (iScreenHeight - (m_rtWindow.bottom - m_rtWindow.top)) / 2;
	MoveWindow(m_hWnd, x, y, m_rtClient.right, m_rtClient.bottom, true);
}

LRESULT CALLBACK Window::MsgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CREATE:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_LBUTTONDOWN:
		DestroyWindow(hwnd);
		return 0;
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	assert(g_pWindow != nullptr);

	LRESULT ret;
	if (ret = g_pWindow->MsgProc(hwnd, msg, wparam, lparam))
	{
		return ret;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}