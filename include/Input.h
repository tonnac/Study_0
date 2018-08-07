#pragma once
#include "Std.h"

enum KEYSTATE
{
	KEY_FREE,
	KEY_PUSH,
	KEY_HOLD,
	KEY_UP
};

class KInput : public Singleton<KInput>
{
	friend class Singleton<KInput>;
	KInput() {}
public:
	bool				Init();
	bool				Frame();
	bool				Render();
	bool				Release();
public:
	DWORD				getMouse(DWORD);
	DWORD				getKey(DWORD);
	void				MsgEvent(MSG);
private:
	DWORD				KeyCheck(DWORD);
private:
	TCHAR				m_csBuffer[256];
	POINT				m_MousePos;
	DWORD				m_dwKeyState[256];
	DWORD				m_dwBeforeMouseState[3];
	DWORD				m_dwCurrentMouseState[3];
};

#define I_KInput KInput::getInstance()