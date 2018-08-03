#pragma once
#include "Std.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

class Window
{
public:
	bool SetWindow(HINSTANCE hinst, const TCHAR * pTitieName = L"KGCA Sample",
							UINT iWidth = 800, UINT iHeight = 600);
	bool Run();
	void Set(DWORD m_dwStyle);
public:
	virtual bool		GameInit();
	virtual bool		GameRun();
	virtual bool		GameRelease();
	virtual LRESULT CALLBACK MsgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
public:
	Window();
	virtual	~Window();
private:
	HWND		m_hWnd;
	HINSTANCE	m_hInstance;
	RECT		m_rtClient;
	RECT		m_rtWindow;
	DWORD		m_dwStyle;
private:
	void CenterWindow();
};
