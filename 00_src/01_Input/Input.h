#pragma once
#include "Std.h"

enum class KEYSTATE {
	KEY_FREE = 0,
	KEY_PUSH,
	KEY_UP,
	KEY_HOLD
};

class Input : public Singleton<Input>
{
	friend class Singleton<Input>;
public:
	KEYSTATE	getKey(DWORD dwKey);
	KEYSTATE	m_dwMouseState[3];
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
	KEYSTATE	KeyCheck(DWORD dwKey);
	KEYSTATE	m_dwKeyState[256];
	KEYSTATE	m_dwBeforeMouseState[3];
};

#define I_input Input::getInstance()