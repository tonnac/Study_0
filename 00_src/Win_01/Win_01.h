#pragma once
#include "Std.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);



class Window
{
public:
	bool SetWindow(HINSTANCE, const TCHAR* = L"Default");
	bool Run();
public:
	void SetStyle(DWORD);
	virtual LRESULT CALLBACK MsgProc(HWND, UINT, WPARAM, LPARAM);
public:
	Window();
	~Window();
private:
	virtual bool GameRun();
	virtual bool GameInit();
	virtual bool GameRelease();
	void CenterWindow();
private:
	HINSTANCE m_hInst;
	HWND m_hWnd;
	RECT m_rtClient;
	RECT m_rtWindow;
	DWORD m_dwStyle;
};
