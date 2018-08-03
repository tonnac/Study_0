#include "Timer.h"

bool Timer::Init()
{
	m_dwBeforeTick = timeGetTime();
	return true;
}
bool Timer::Frame()
{
	DWORD dwCurrentTick = timeGetTime();
	DWORD ElapsedTick = dwCurrentTick - m_dwBeforeTick;
	m_fSecPerFrame = ElapsedTick / 1000.0f;
	m_fGameTime += m_fSecPerFrame;
	m_fTimer += m_fSecPerFrame;
	if (m_fTimer >= 1.0)
	{
		m_fTimer -= 1.0;
		_stprintf_s(m_dBuffer, L"FPS:%d, Time:%5.3f, SPF:%5.3f", m_dwFrameCount, m_fGameTime, m_fSecPerFrame);
		m_dwFrameCount = 0;
	}
	m_dwFrameCount++;
	m_dwBeforeTick = dwCurrentTick;
	return true;
}
bool Timer::Render()
{
	HDC hdc = GetDC(g_hWnd);
	TextOut(hdc, 0, 0, m_dBuffer, wcsnlen_s(m_dBuffer,256));
	
	ReleaseDC(g_hWnd, hdc);
	return true;
}
bool Timer::Release()
{
	return true;
}