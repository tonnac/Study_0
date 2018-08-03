#pragma once
#include "Std.h"
#include "Input.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

class Window
{
public:
	Window();
public:
	bool			setWindow(HINSTANCE);
	bool			Run();
public:
	virtual LRESULT CALLBACK MsgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
protected:
	virtual bool	GameInit();
	virtual bool	GameRun();
	virtual bool	GameRelease();
private:
	void			CenterWindow();
	void			MsgEvent(MSG msg);
private:
	HWND			m_hWnd;
	RECT			m_rtClient;
	RECT			m_rtWindow;
};