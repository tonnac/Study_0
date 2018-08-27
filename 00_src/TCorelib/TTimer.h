#pragma once
#include "TStd.h"
/*
 1) 1�������� ��� �ð�=m_fSecPerFrame
 2) 1���� ������ ī����
 3) ������ ����� �����ð�
*/
class TTimer
{
	DWORD m_dwFrameCount;
	DWORD m_dwFPS;
	DWORD m_dwBeforeTick;
	float m_fSecPerFrame;
	float m_fGameTimer;
	float m_fTimer;
	TCHAR m_csBuffer[256];
public:
	bool	Init();		// �ʱ�ȭ
	bool	Frame();	// ���
	bool	Render();	// ��ο�
	bool	Release();	// �Ҹ�, ����
public:
	TTimer();
	virtual ~TTimer();
};

