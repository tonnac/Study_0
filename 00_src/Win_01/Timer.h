#pragma once
#include "Std.h"

class Timer
{
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
private:
	TCHAR m_dBuffer[256];
	DWORD m_dwFPS;
	DWORD m_dwBeforeTick;
	DWORD m_dwFrameCount;
	float m_fSecPerFrame;
	float m_fGameTime;
	float m_fTimer;
};