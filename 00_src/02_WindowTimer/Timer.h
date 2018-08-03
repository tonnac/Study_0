#pragma once
#include "Std.h"
/*
 1) 1�������� ��� �ð� = m_fSecPerFrame
 2) 1���� ������ ī����
 3) ���� ����� �ð� = m_fGameTimer
*/
class Timer
{
public:
	bool	Init();		// �ʱ�ȭ
	bool	Frame();	// ���
	bool	Render();	// ��ο�
	bool	Release();	// �Ҹ�,����
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