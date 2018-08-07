#pragma once
#include "Std.h"
#include "Input.h"

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

class KWindow
{
public:
	KWindow();
public:
	RECT						getrtClient();
	bool						SetWindow(HINSTANCE);
	bool						Run();
	virtual LRESULT	CALLBACK	MsgProc(HWND, UINT, WPARAM, LPARAM);
private:
	virtual	bool				GameInit();
	virtual	bool				GameFrame();
	virtual bool				GameRender();
	virtual bool				GameRelease();
private:
	void						CenterWindow();
private:
	virtual bool				Init();
	virtual bool				Frame();
	virtual bool				Render();
	virtual bool				Release();
protected:
	RECT						m_rtClient;
	RECT						m_rtWindow;
	WNDCLASSEX					m_wdClass;
	HINSTANCE					m_hInstance;
	HWND						m_hWnd;
};