#pragma once
#include "TStd.h"
enum KeyState
{
	KEY_FREE = 0,
	KEY_PUSH,
	KEY_UP,
	KEY_HOLD,
};
class TInput : public TSingleton<TInput>
{
	friend class TSingleton<TInput>;
	DWORD	KeyCheck(DWORD dwKey);
	DWORD  m_dwKeyState[256];
	DWORD  m_dwBeforeMouseState[3];
public:
	DWORD  m_dwMouseState[3];	
	POINT  m_MousePos;
public:	
	DWORD   Key(DWORD dwKey);
	void	MsgEvent(MSG msg);
	bool	Init();		// 초기화
	bool	Frame();	// 계산
	bool	Render();	// 드로우
	bool	Release();	// 소멸, 삭제
protected:
	TInput();
	virtual ~TInput();
};
#define I_Input TInput::GetInstance()
