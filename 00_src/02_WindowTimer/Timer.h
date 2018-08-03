#pragma once
#include "Std.h"
/*
 1) 1프레임의 경과 시간 = m_fSecPerFrame
 2) 1초의 프레임 카운터
 3) 게임 실행된 시간 = m_fGameTimer
*/
class Timer
{
public:
	bool	Init();		// 초기화
	bool	Frame();	// 계산
	bool	Render();	// 드로우
	bool	Release();	// 소멸,삭제
public:
	Timer();
	virtual ~Timer();
private:
	DWORD m_dwBeforeTick;
	DWORD m_dwFPS;
	DWORD m_dwFrameCount;
	float m_fTimer;
	float m_fSecPerFrame;
	float m_fGameTimer;
	TCHAR m_csBuffer[256];
};