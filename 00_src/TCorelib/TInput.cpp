#include "TInput.h"

DWORD TInput::KeyCheck(DWORD dwKey)
{
	if (g_bActiveApp == false) KEY_FREE;
	// GetKeyState() // 동기적
	// GetAsyncKeyState()//비동기적
	SHORT sKey = GetAsyncKeyState(dwKey);	
	// 0x8000 : 이전X ~ 지금O
	// 0x8001 : 이전O ~ 지금O
	// 0x0000 : 이전X ~ 지금X
	// 0x0001 : 이전O ~ 지금X
	if (sKey & 0x8000)
	{
		if (m_dwKeyState[dwKey] == KEY_FREE ||
			m_dwKeyState[dwKey] == KEY_UP)
		{
			m_dwKeyState[dwKey] = KEY_PUSH;
		}
		else
		{
			m_dwKeyState[dwKey] = KEY_HOLD;
		}
	}
	else
	{
		if(m_dwKeyState[dwKey] == KEY_PUSH ||
			m_dwKeyState[dwKey] == KEY_HOLD)
		{
			m_dwKeyState[dwKey] = KEY_UP;
		}
		else
		{
			m_dwKeyState[dwKey] = KEY_FREE;
		}
	}
	return m_dwKeyState[dwKey];
}

bool	TInput::Init() 
{	
	ZeroMemory(m_dwKeyState, sizeof(DWORD) * 256);
	ZeroMemory(m_dwMouseState, sizeof(DWORD) * 3);
	ZeroMemory(m_dwBeforeMouseState, sizeof(DWORD) * 3);
	return true;
}
bool	TInput::Frame() 
{
	GetCursorPos(&m_MousePos); //  화면좌표
	ScreenToClient(g_hWnd, &m_MousePos);
	
	for (int iKey = 0; iKey < 255; iKey++)
	{
		m_dwKeyState[iKey] = KeyCheck(iKey);
	}
	for (int iButton = 0; iButton < 3; iButton++)
	{
		if (m_dwBeforeMouseState[iButton] == KEY_PUSH)
		{
			if (m_dwMouseState[iButton] == KEY_PUSH)
			{
				m_dwMouseState[iButton] = KEY_HOLD;
			}
		}
		if (m_dwBeforeMouseState[iButton] == KEY_UP)
		{
			if (m_dwMouseState[iButton] == KEY_UP)
			{
				m_dwMouseState[iButton] = KEY_FREE;
			}
		}
		m_dwBeforeMouseState[iButton] = m_dwMouseState[iButton];
	}
	return true;
}
bool	TInput::Render() {
	
	return true;
}
DWORD   TInput::Key(DWORD dwKey)
{
	return m_dwKeyState[dwKey];
}
bool	TInput::Release() {
	return true;
}
void	TInput::MsgEvent(MSG msg)
{	
	switch (msg.message)
	{
	case WM_LBUTTONDOWN:
	{
		m_dwMouseState[0] = KEY_PUSH;
	}break;
	case WM_LBUTTONUP:
	{
		m_dwMouseState[0] = KEY_UP;
	}break;
	case WM_RBUTTONDOWN:
	{
		m_dwMouseState[1] = KEY_PUSH;
	}break;
	case WM_RBUTTONUP:
	{
		m_dwMouseState[1] = KEY_UP;
	}break;
	case WM_MBUTTONDOWN:
	{
		m_dwMouseState[2] = KEY_PUSH;
	}break;
	case WM_MBUTTONUP:
	{
		m_dwMouseState[2] = KEY_UP;
	}break;
	}
}
TInput::TInput()
{
}


TInput::~TInput()
{
}
