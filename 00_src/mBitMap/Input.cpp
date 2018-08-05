#include "Input.h"


bool KInput::Init()
{
	ZeroMemory(m_dwKeyState, sizeof(DWORD) * 256);
	ZeroMemory(m_dwBeforeMouseState, sizeof(DWORD) * 3);
	ZeroMemory(m_dwCurrentMouseState, sizeof(DWORD) * 3);

	ZeroMemory(m_csBuffer, sizeof(TCHAR) * 256);
	return true;
}
bool KInput::Frame()
{
	GetCursorPos(&m_MousePos);
	ScreenToClient(g_hWnd, &m_MousePos);
	_stprintf_s(m_csBuffer, L"X : %d   Y : %d", m_MousePos.x, m_MousePos.y);
	for (int i = 0; i < 256; ++i)
	{
		m_dwKeyState[i] = KeyCheck(i);
	}
	for (int iButton = 0; iButton < 3; ++iButton)
	{
		if (m_dwBeforeMouseState[iButton] == KEY_PUSH)
		{
			if (m_dwCurrentMouseState[iButton] == KEY_PUSH)
			{
				m_dwCurrentMouseState[iButton] = KEY_HOLD;
			}
		}
		if (m_dwBeforeMouseState[iButton] == KEY_UP)
		{
			if (m_dwCurrentMouseState[iButton] == KEY_UP)
			{
				m_dwCurrentMouseState[iButton] = KEY_FREE;
			}
		}
		m_dwBeforeMouseState[iButton] = m_dwCurrentMouseState[iButton];
	}
	return true;
}
bool KInput::Render()
{
	TextOut(g_hOffScreenDC, 0,17, m_csBuffer, static_cast<int>(_tcslen(m_csBuffer)));
	return true;
}
bool KInput::Release()
{
	return true;
}
DWORD KInput::getMouse(DWORD dwKey)
{
	switch (dwKey)
	{
	case VK_LBUTTON:
		return m_dwCurrentMouseState[0];
	case VK_MBUTTON:
		return m_dwCurrentMouseState[1];
	case VK_RBUTTON:
		return m_dwCurrentMouseState[2];
	default:
		return -1;
	}
}
DWORD KInput::getKey(DWORD dwKey)
{
	return m_dwKeyState[dwKey];
}
void KInput::MsgEvent(MSG msg)
{
	switch (msg.message)
	{
	case WM_LBUTTONDOWN:
		m_dwCurrentMouseState[0] = KEY_PUSH;
		break;
	case WM_LBUTTONUP:
		m_dwCurrentMouseState[0] = KEY_UP;
		break;
	case WM_MBUTTONDOWN:
		m_dwCurrentMouseState[1] = KEY_PUSH;
		break;
	case WM_MBUTTONUP:
		m_dwCurrentMouseState[1] = KEY_UP;
		break;
	case WM_RBUTTONDOWN:
		m_dwCurrentMouseState[2] = KEY_PUSH;
		break;
	case WM_RBUTTONUP:
		m_dwCurrentMouseState[2] = KEY_UP;
		break;
	}
}
DWORD KInput::KeyCheck(DWORD dwKey)
{
	SHORT sKey = GetAsyncKeyState(dwKey);
	if (sKey & 0x8000)
	{
		if (m_dwKeyState[dwKey] == KEY_UP ||
			m_dwKeyState[dwKey] == KEY_FREE)
			m_dwKeyState[dwKey] = KEY_PUSH;
		else
			m_dwKeyState[dwKey] = KEY_HOLD;
	}
	else
	{
		if (m_dwKeyState[dwKey] == KEY_PUSH ||
			m_dwKeyState[dwKey] == KEY_HOLD)
			m_dwKeyState[dwKey] = KEY_UP;
		else
			m_dwKeyState[dwKey] = KEY_FREE;
	}
	return m_dwKeyState[dwKey];
}