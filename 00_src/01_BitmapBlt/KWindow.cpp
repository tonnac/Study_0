#include "KWindow.h"

TCHAR	csBuffer[256];
DWORD	dwFPS = 0;
DWORD	dw100Frame = 0;
float	g_fPerSerFrame = 0.0;
float	g_fGameTime = 0.0;
float	g_fTime = 0.0;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}



bool KWindow::Init()
{
	WNDCLASSEX wd;
	ZeroMemory(&wd, sizeof(WNDCLASSEX));
	wd.cbSize = sizeof(WNDCLASSEX);
	wd.style = CS_VREDRAW | CS_HREDRAW;
	wd.lpfnWndProc = WndProc;
	wd.hInstance = m_hInstance;
	wd.lpszClassName = L"QWE";

	if (!RegisterClassEx(&wd))
	{
		return false;
	}
	m_hWnd = CreateWindowEx(WS_EX_APPWINDOW,			//TOPMOST
		wd.lpszClassName,
		L"WINDOW",
		WS_OVERLAPPEDWINDOW,
		0,0,
		800,600,
		nullptr,
		nullptr,
		wd.hInstance,
		nullptr);
	if (m_hWnd == nullptr)
	{
		return false;
	}
	ShowWindow(m_hWnd, SW_SHOW);

	HBITMAP hBitmap = (HBITMAP)LoadImage(m_hInstance, L"bitmap1.bmp",
		IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);

	HDC hdc = GetDC(m_hWnd);
	HDC hMemDC = CreateCompatibleDC(hdc);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);

	DWORD dwTick = timeGetTime();

	MSG msg;
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
			DWORD dwCurreintTick = timeGetTime();
			DWORD dwElapstedTick = dwCurreintTick - dwTick;		
			g_fPerSerFrame = dwElapstedTick / 1000.0f;
			g_fGameTime += g_fPerSerFrame;
			g_fTime += g_fPerSerFrame;
			if (g_fTime >= 1.0f)
			{
				g_fTime -= 1.0f;
				_stprintf_s(csBuffer, L"FPS : %d  Time : %5.5f  SPF : %5.5f", dwFPS, g_fGameTime, g_fPerSerFrame);
				dwFPS = 0;
			}
			dwFPS++;
			dwTick = dwCurreintTick;
			dw100Frame += dwElapstedTick;
			if (dw100Frame < 100)
			{
				continue;
			}
			dw100Frame = 0;
			BitBlt(hdc, 20, 20, 800, 600,
				hMemDC, 0, 0, SRCCOPY);
			TextOut(hdc, 0, 0, csBuffer, (int)wcslen(csBuffer));
		}
	}
	DeleteObject(hBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(hMemDC);
	ReleaseDC(m_hWnd, hdc);
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

KWindow::KWindow(HINSTANCE hinst) : m_hInstance(hinst)
{}


KWindow::~KWindow()
{
}
