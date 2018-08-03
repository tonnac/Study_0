#pragma once
#include "Std.h"

class Timer
{
public:
	Timer();
public:
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
private:
	TCHAR		m_csBuffer[256];
	DWORD		m_dwFrameCount;
	DWORD		m_dwBeforeTick;
	float		m_fSecPerFrame;
	float		m_fGameTime;
	float		m_fTimer;
};