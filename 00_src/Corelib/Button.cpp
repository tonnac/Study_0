#include "Button.h"

bool Button::Init()
{
	return true;
}
bool Button::Frame()
{
	m_rtCollision.left = m_posDraw.x;
	m_rtCollision.top = m_posDraw.y;
	m_rtCollision.right = m_rtCollision.left + m_rtDraw.right;
	m_rtCollision.bottom = m_rtCollision.top + m_rtDraw.bottom;

	m_BtnCurrent = m_BtnColorBitmap[Btn_Normal];
	if (Collision::RectInPt(m_rtCollision, I_KInput.m_MousePos))
	{
		m_BtnCurrent = m_BtnColorBitmap[Btn_Hover];
		if (I_KInput.getMouse(VK_LBUTTON) == KEY_PUSH || I_KInput.getMouse(VK_LBUTTON) == KEY_HOLD)
		{
			m_BtnCurrent = m_BtnColorBitmap[Btn_Click];
		}
	}
	return true;
}
bool Button::Render()
{
	if (m_MaskBitmap == nullptr)
	{
		BitBlt(g_hOffScreenDC,
			static_cast<int>(m_posDraw.x),
			static_cast<int>(m_posDraw.y),
			m_rtDraw.right, m_rtDraw.bottom,
			m_BtnCurrent->m_hMemDC,
			m_rtDraw.left, m_rtDraw.top,
			SRCCOPY);
		return true;
	}
	BitBlt(g_hOffScreenDC,
		static_cast<int>(m_posDraw.x),
		static_cast<int>(m_posDraw.y),
		m_rtDraw.right, m_rtDraw.bottom,
		m_BtnCurrent->m_hMemDC,
		m_rtDraw.left, m_rtDraw.top,
		SRCAND);
	BitBlt(g_hOffScreenDC,
		static_cast<int>(m_posDraw.x),
		static_cast<int>(m_posDraw.y),
		m_rtDraw.right, m_rtDraw.bottom,
		m_BtnCurrent->m_hMemDC,
		m_rtDraw.left, m_rtDraw.top,
		SRCINVERT);
	BitBlt(g_hOffScreenDC,
		static_cast<int>(m_posDraw.x),
		static_cast<int>(m_posDraw.y),
		m_rtDraw.right, m_rtDraw.bottom,
		m_BtnCurrent->m_hMemDC,
		m_rtDraw.left, m_rtDraw.top,
		SRCINVERT);
	return true;
}
bool Button::Release()
{
	return true;
}

bool Button::LoadFile(const TCHAR* szColorFile, const TCHAR* szMaskFile, int iState)
{
	int index = I_BitmapMgr.Load(szColorFile);
	m_BtnColorBitmap[iState] = I_BitmapMgr.getPtr(index);
//	assert(m_ColorBitmap != nullptr);
	if (szMaskFile != nullptr)
	{
		index = I_BitmapMgr.Load(szMaskFile);
		m_BtnMaskBitmap[iState] = I_BitmapMgr.getPtr(index);
	}
	m_BtnCurrent = m_BtnColorBitmap[0];
	return true;
}
Button::Button()
{
}


Button::~Button()
{
}
