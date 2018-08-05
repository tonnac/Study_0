#pragma once
#include "Std.h"

class KTimer
{
public:
	KTimer();
public:
	bool				Init();
	bool				Frame();
	bool				Render();
	bool				Release();
private:
	TCHAR				m_csBuffer[256];
	DWORD				m_dwFrame;
	DWORD				m_dwBeforeTick;
	float				m_fTimer;
	float				m_fSecPerFrame;
	float				m_fGameTime;
};