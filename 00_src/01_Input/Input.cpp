#include "Input.h"


KEYSTATE Input::getKey(DWORD dwKey)
{
	return m_dwKeyState[dwKey];
}
bool Input::Init()
{
	ZeroMemory(m_dwKeyState, sizeof(KEYSTATE) * 256);
	ZeroMemory(m_dwMouseState, sizeof(KEYSTATE) * 3);
	ZeroMemory(m_dwBeforeMouseState, sizeof(KEYSTATE) * 3);
	return true;
}
bool Input::Frame()
{
	GetCursorPos(&m_MousePos);
	ScreenToClient(g_hWnd, &m_MousePos);
	for (int i = 0; i < 256; ++i)
	{
		m_dwKeyState[i] = KeyCheck(i);
	}
	for (int iButton = 0; iButton < 3; ++iButton)
	{
		if (m_dwBeforeMouseState[iButton] == KEYSTATE::KEY_PUSH)
		{
			if (m_dwMouseState[iButton] == KEYSTATE::KEY_PUSH)
			{
				m_dwMouseState[iButton] = KEYSTATE::KEY_HOLD;
			}
		}
		if (m_dwBeforeMouseState[iButton] == KEYSTATE::KEY_UP)
		{
			if (m_dwMouseState[iButton] == KEYSTATE::KEY_UP)
			{
				m_dwMouseState[iButton] = KEYSTATE::KEY_FREE;
			}
		}
		m_dwBeforeMouseState[iButton] = m_dwMouseState[iButton];
	}
	return true;
}
bool Input::Render()
{
	return true;
}
bool Input::Release()
{
	return true;
}

void Input::MsgEvent(MSG msg)
{
	switch (msg.message)
	{
	case WM_MBUTTONDOWN:
		m_dwMouseState[0] = KEYSTATE::KEY_PUSH;
		break;
	case WM_MBUTTONUP:
		m_dwMouseState[0] = KEYSTATE::KEY_UP;
		break;
	case WM_LBUTTONDOWN:
		m_dwMouseState[1] = KEYSTATE::KEY_PUSH;
		break;
	case WM_LBUTTONUP:
		m_dwMouseState[1] = KEYSTATE::KEY_UP;
		break;
	case WM_RBUTTONDOWN:
		m_dwMouseState[2] = KEYSTATE::KEY_PUSH;
		break;
	case WM_RBUTTONUP:
		m_dwMouseState[2] = KEYSTATE::KEY_UP;
		break;
	}
}

KEYSTATE Input::KeyCheck(DWORD dwKey)
{
	SHORT sKey = GetAsyncKeyState(dwKey);
	if (sKey & 0x8000)
	{
		if (m_dwKeyState[dwKey] == KEYSTATE::KEY_FREE ||
			m_dwKeyState[dwKey] == KEYSTATE::KEY_UP)
			m_dwKeyState[dwKey] = KEYSTATE::KEY_PUSH;
		else
			m_dwKeyState[dwKey] = KEYSTATE::KEY_HOLD;

	}
	else
	{
		if (m_dwKeyState[dwKey] == KEYSTATE::KEY_HOLD ||
			m_dwKeyState[dwKey] == KEYSTATE::KEY_PUSH)
			m_dwKeyState[dwKey] = KEYSTATE::KEY_UP;
		else
			m_dwKeyState[dwKey] = KEYSTATE::KEY_FREE;
	}
	return m_dwKeyState[dwKey];
}