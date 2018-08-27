#include "TButton.h"
#include "TInput.h"
bool	TButton::LoadUI(const TCHAR* pszColor,
	const TCHAR* pszMask, int iState)
{
	int iIndex = I_BitmapMgr.Load(pszColor);
	m_hBtnColorBitmap[iState] = I_BitmapMgr.GetPtr(iIndex);
	if (pszMask != NULL)
	{
		iIndex = I_BitmapMgr.Load(pszMask);
		m_hBtnMaskBitmap[iState] = I_BitmapMgr.GetPtr(iIndex);
	}
	m_hBtnCurrentBitmap = m_hBtnColorBitmap[0];
	return true;
};

bool	TButton::Frame()
{
	m_hBtnCurrentBitmap = m_hBtnColorBitmap[Btn_Normal];
	if (TCollision::RectInPt(
		m_rtCollision, I_Input.m_MousePos))
	{
		m_hBtnCurrentBitmap = m_hBtnColorBitmap[Btn_Hover];
		if (I_Input.Key(VK_LBUTTON))
		{
			m_hBtnCurrentBitmap = m_hBtnColorBitmap[Btn_Click];
		}		
	}
	return true;
}

bool	TButton::Render()
{
	BitBlt(g_hOffScreenDC,
		m_posDraw.x, m_posDraw.y,
		m_rtDraw.right,
		m_rtDraw.bottom,
		m_hBtnCurrentBitmap->m_hMemDC,
		m_rtDraw.left,
		m_rtDraw.top, SRCCOPY);
	return true;
}
TButton::TButton()
{
}


TButton::~TButton()
{
}
