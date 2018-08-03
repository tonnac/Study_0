#include "Win_01.h"

Window * g_pWindow = nullptr;
HWND g_hWnd;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	assert(g_pWindow != nullptr);

	LRESULT Ret;
	if (Ret = g_pWindow->MsgProc(hWnd, msg, wparam, lparam))
	{
		return Ret;
	}
	return DefWindowProc(hWnd, msg, wparam, lparam);
}

LRESULT CALLBACK Window::MsgProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_MBUTTONDOWN:
		DestroyWindow(hWnd);
		return 0;
	}
	return 0;
}

bool Window::SetWindow(HINSTANCE hInst, const TCHAR* pTitleName)
{
	m_hInst = hInst;
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInst;
	wc.lpszClassName = L"QWE";
	wc.lpszMenuName = pTitleName;
	wc.lpfnWndProc = WndProc;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	if (!RegisterClassEx(&wc))
	{
		return false;
	}

	m_hWnd = CreateWindowEx(WS_EX_APPWINDOW,
		wc.lpszClassName,
		pTitleName,
		WS_POPUPWINDOW, 
		100, 
		100, 
		400, 
		400,
		nullptr, 
		nullptr, 
		hInst, 
		nullptr);

	if (m_hWnd == nullptr)
	{
		return false;
	}
	g_hWnd = m_hWnd;
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
			Sleep(1);
			GameRun();
		}
	}
	return GameRelease();
}

void Window::SetStyle(DWORD dwStyle)
{
	m_dwStyle = dwStyle;
}

Window::Window() : m_dwStyle(WS_OVERLAPPEDWINDOW)
{
	g_pWindow = this;
}
Window::~Window()
{

}

bool Window::GameRun()
{
	return true;
}
bool Window::GameInit()
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
	int x = (iScreenWidth - (m_rtWindow.right - m_rtWindow.left)) / 2;
	int y = (iScreenHeight - (m_rtWindow.bottom - m_rtWindow.top)) / 2;
	MoveWindow(m_hWnd, x, y, m_rtClient.right, m_rtClient.bottom, true);
}