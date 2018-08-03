#include "Timer.h"

Timer::Timer()
{
	m_dwFrameCount = 0;
	m_fSecPerFrame = 0.0f;
	m_fGameTime = 0.0f;
	m_fTimer = 0.0f;
}

bool Timer::Init()
{
	m_dwBeforeTick = timeGetTime();
	ZeroMemory(m_csBuffer, sizeof(TCHAR) * 256);
	return true;
}
bool Timer::Frame()
{
	DWORD dwCurrentTick = timeGetTime();
	DWORD ElapstedTick = dwCurrentTick - m_dwBeforeTick;
	m_fSecPerFrame = ElapstedTick / 1000.0f;

	m_fGameTime += m_fSecPerFrame;
	m_fTimer += m_fSecPerFrame;

	if (m_fTimer >= 1.0f)
	{
		m_fTimer -= 1.0f;
		_stprintf_s(m_csBuffer, L"FPS : %d  Time : %4.3f", m_dwFrameCount, m_fGameTime);
	//	OutputDebugString(m_csBuffer);
		m_dwFrameCount = 0;
	}
	m_dwFrameCount++;
	m_dwBeforeTick = dwCurrentTick;
	return true;
}
bool Timer::Render()
{
	HDC hdc = GetDC(g_hWnd);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(255, 255, 255));
	TextOut(hdc, 0, 0, m_csBuffer, (int)wcslen(m_csBuffer));

	ReleaseDC(g_hWnd, hdc);
	return true;
}
bool Timer::Release()
{
	return true;
}