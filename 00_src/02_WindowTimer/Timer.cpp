#include "Timer.h"

bool Timer::Init()
{
	m_dwBeforeTick = timeGetTime();  // 정밀도 1 / 1000
	return true;
}
bool Timer::Frame()
{
	// timeGetTime(); winmm.lib 추가
	DWORD dwCurrentTick = timeGetTime();
	DWORD dwElapsedTick = dwCurrentTick - m_dwBeforeTick;
	m_fSecPerFrame = dwElapsedTick / 1000.0f;
	m_fGameTimer += m_fSecPerFrame;

	m_fTimer += m_fSecPerFrame;
	if (m_fTimer >= 1.0f)
	{
		m_dwFPS = m_dwFrameCount;
		m_dwFrameCount = 0;
		m_fTimer -= 1.0f;
		_stprintf_s(m_csBuffer, L"FPS:%d, TIME:%5.4f, SPF:%5.4f", m_dwFPS, m_fGameTimer,m_fSecPerFrame);
		// OutputDebugString(m_csBuffer); VC출력창에 출력
	}
	m_dwFrameCount++;
	m_dwBeforeTick = dwCurrentTick;
	return true;
}
bool Timer::Render()
{
	HDC hdc = GetDC(g_hWnd);
	TextOut(hdc, 0, 0, m_csBuffer, wcslen(m_csBuffer));


	ReleaseDC(g_hWnd, hdc);
	return true;
}
bool Timer::Release()
{
	return true;
}

Timer::Timer()
{

}


Timer::~Timer()
{
	m_dwBeforeTick = 0;
	m_dwFPS = 0;
	m_dwFrameCount = 0;
	m_fTimer = 0.0f;
	m_fSecPerFrame = 0.0f;
	m_fGameTimer = 0.0f;
}
