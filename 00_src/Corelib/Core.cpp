#include "Core.h"

HDC g_hOffScreenDC = nullptr;

bool Core::GameInit()
{
	m_hScreenDC = GetDC(g_hWnd);
	m_hOffScreenDC = CreateCompatibleDC(m_hScreenDC);
	g_hOffScreenDC = m_hOffScreenDC;
	m_hoffScreenBitmap = CreateCompatibleBitmap(m_hScreenDC, m_rtClient.right, m_rtClient.bottom);
	SelectObject(m_hOffScreenDC, m_hoffScreenBitmap);
	COLORREF bkColor = RGB(0, 0, 0);
	m_hbrBack = CreateSolidBrush(bkColor);
	SelectObject(m_hOffScreenDC, m_hbrBack);
	m_Timer.Init();
	I_input.Init();
	Init();
	return true;
}
bool Core::GameRun()
{
	GameFrame();
	GameRender();
	return true;
}
bool Core::GameRelease()
{
	
	Relaese();
	m_Timer.Release();
	I_input.Release();


	DeleteObject(m_hoffScreenBitmap);
	ReleaseDC(g_hWnd, m_hScreenDC);
	ReleaseDC(g_hWnd, m_hOffScreenDC);

	return true;
}

bool Core::GameFrame()
{
	m_Timer.Frame();
	I_input.Frame();
	Frame();
	return true;
}
bool Core::GamePreRender()
{
	PatBlt(m_hOffScreenDC, 0, 0, m_rtClient.right, m_rtClient.bottom, PATCOPY);
	return true;
}
bool Core::GamePostRender()
{
	BitBlt(m_hScreenDC, 0, 0, m_rtClient.right, m_rtClient.bottom, m_hOffScreenDC, 0, 0, SRCCOPY);
	return true;
}
bool Core::GameRender()
{
	if(GamePreRender())
	{
		Render();
		m_Timer.Render();
		I_input.Render();
	}
	GamePostRender();
	return true;
}

bool Core::Init()
{
	return true;
}
bool Core::Frame()
{
	return true;
}
bool Core::Render()
{
	return true;
}
bool Core::Relaese()
{
	
	return true;
}