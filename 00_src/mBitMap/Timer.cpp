#include "Timer.h"

float g_fSecPerFrame = 0.0f;

KTimer::KTimer()
{
	ZeroMemory(m_csBuffer, sizeof(TCHAR) * 256);
	m_dwFrame = 0;
	m_dwBeforeTick = 0;
	m_fTimer = 0.0f;
	m_fSecPerFrame = 0.0f;
	m_fGameTime = 0.0f;
}
bool KTimer::Init()
{
	m_dwBeforeTick = timeGetTime();
	return true;
}
bool KTimer::Frame()
{
	DWORD dwCurrentTick = timeGetTime();
	DWORD ElapstedTick = dwCurrentTick - m_dwBeforeTick;
	m_fSecPerFrame = g_fSecPerFrame = ElapstedTick / 1000.0f;
	m_fGameTime += m_fSecPerFrame;
	m_fTimer += m_fSecPerFrame;

	if (m_fTimer >= 1.0f)
	{
		m_fTimer -= 1.0f;
		_stprintf_s(m_csBuffer, L"FPS : %d     Time : %5.4f     SPF : %5.4f", m_dwFrame, m_fGameTime, m_fSecPerFrame);
//		OutputDebugString(m_csBuffer);
		m_dwFrame = 0;
	}
	m_dwFrame++;
	m_dwBeforeTick = timeGetTime();
	return true;
}
bool KTimer::Render()
{
	SetTextColor(g_hOffScreenDC, RGB(102, 255, 255));
	SetBkColor(g_hOffScreenDC, RGB(0, 0, 0));
	TextOut(g_hOffScreenDC, 0, 0, m_csBuffer,static_cast<int>(_tcsclen(m_csBuffer)));
	return true;
}
bool KTimer::Release()
{
	return true;
}