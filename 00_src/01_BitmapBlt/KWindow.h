#pragma once

#include <windows.h>
#include <tchar.h>

#pragma comment(lib,"winmm.lib")

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);


class KWindow
{
public:
	bool			Init();
	bool			Frame();
	bool			Render();
	bool			Release();
public:
	KWindow(HINSTANCE hinst);
	~KWindow();
private:
	HWND			m_hWnd;
	HINSTANCE		m_hInstance;
};