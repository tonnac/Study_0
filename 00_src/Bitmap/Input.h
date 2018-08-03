#pragma once
#include "Std.h"

enum KEYSTATE {
	KEY_FREE = 0,
	KEY_PUSH,
	KEY_UP,
	KEY_HOLD
};

class Input : public Singleton<Input>
{
	friend class Singleton<Input>;
public:
	DWORD		getKey(DWORD dwKey);
	DWORD		m_dwMouseState[3];
	POINT		m_MousePos;
public:
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
public:
	void		MsgEvent(MSG msg);
private:
	Input() {}
	DWORD		KeyCheck(DWORD dwKey);
	DWORD		m_dwKeyState[256];
	DWORD		m_dwBeforeMouseState[3];
};

#define I_input Input::getInstance()