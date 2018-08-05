#include "Core.h"

HDC	g_hOffScreenDC = nullptr;

bool KCore::GameInit()
{
	m_hOnScreenDC = GetDC(g_hWnd);
	m_hOffScreenDC = g_hOffScreenDC = CreateCompatibleDC(m_hOnScreenDC);
	m_hOffBitmap = CreateCompatibleBitmap(m_hOnScreenDC, m_rtWindow.right, m_rtWindow.bottom);
	SelectObject(m_hOffScreenDC, m_hOffBitmap);

	COLORREF ref = RGB(255, 255, 153);
	m_hBkColor = CreateSolidBrush(ref);
	SelectObject(m_hOffScreenDC, m_hBkColor);

	m_Timer.Init();
	I_KInput.Init();
	Init();
	return true;
}
bool KCore::GameFrame()
{
	m_Timer.Frame();
	I_KInput.Frame();
	Frame();
	return true;
}
bool KCore::GameRender()
{
	if (GamePreRender())
	{
		Render();
		m_Timer.Render();
		I_KInput.Render();
	}
	return GamePostRender();
}
bool KCore::GameRelease()
{
	Release();
	m_Timer.Release();
	I_KInput.Release();
	return true;
}
bool KCore::Init()
{
	return true;
}
bool KCore::Frame()
{
	return true;
}
bool KCore::Render()
{
	return true;
}
bool KCore::Release()
{
	DeleteDC(m_hOffScreenDC);
	DeleteObject(m_hOffBitmap);
	ReleaseDC(g_hWnd, m_hOnScreenDC);
	return true;
}
bool KCore::GamePreRender()
{
	PatBlt(m_hOffScreenDC, 0, 0, m_rtWindow.right, m_rtWindow.bottom, PATCOPY);
	return true;
}
bool KCore::GamePostRender()
{
	BitBlt(m_hOnScreenDC, 0, 0, m_rtClient.right, m_rtClient.bottom, m_hOffScreenDC, 0, 0, SRCCOPY);
	return true;
}