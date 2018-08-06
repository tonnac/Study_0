#include "KObject.h"

#pragma comment(lib,"msimg32.lib")

bool KObject::Load(const TCHAR* pszColor,
				   const TCHAR* pszMask)
{
	int iIndex = I_BitmapMgr.Load(pszColor); 
	m_pColorBitmap = I_BitmapMgr.getPtr(iIndex);
	if (pszMask != nullptr)
	{
		iIndex = I_BitmapMgr.Load(pszMask);
		m_pMaskBitmap = I_BitmapMgr.getPtr(iIndex);
	}
	return true;
}
bool KObject::Draw(SHORT sType, RECT* rt)
{
	RECT rtDraw = m_rtDraw;
	if (rt == nullptr)
	{
		rtDraw = *rt;
	}
	switch (sType)
	{
	case LR_ROTATION:
		TransparentBlt(g_hOffScreenDC, static_cast<int>(m_pos.x) + rtDraw.right, static_cast<int>(m_pos.y), -rtDraw.right, rtDraw.bottom, m_pColorBitmap->m_hMemDC, rtDraw.left, rtDraw.top, rtDraw.right, rtDraw.bottom, SRCCOPY);
		break;
	case TB_ROTATION:
		TransparentBlt(g_hOffScreenDC, static_cast<int>(m_pos.x), static_cast<int>(m_pos.y) + rtDraw.bottom, rtDraw.right, -rtDraw.bottom, m_pColorBitmap->m_hMemDC, rtDraw.left, rtDraw.top, rtDraw.right, rtDraw.bottom, SRCCOPY);
		break;
	case LRTB_ROTATION:
		TransparentBlt(g_hOffScreenDC, static_cast<int>(m_pos.x) + rtDraw.right, static_cast<int>(m_pos.y) + rtDraw.bottom, -rtDraw.right, -rtDraw.bottom, m_pColorBitmap->m_hMemDC, rtDraw.left, rtDraw.top, rtDraw.right, rtDraw.bottom, SRCCOPY);
		break;
	default:
		TransparentBlt(g_hOffScreenDC, static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), rtDraw.right, rtDraw.bottom, m_pColorBitmap->m_hMemDC, rtDraw.left, rtDraw.top, rtDraw.right, rtDraw.bottom, SRCCOPY);
		break; // 스케일만 조정
	}
	return true;
}
bool KObject::DrawColorKey(DWORD dwMaskColor)
{
	TransparentBlt(g_hOffScreenDC, static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_rtDraw.right, m_rtDraw.bottom, m_pColorBitmap->m_hMemDC, m_rtDraw.left, m_rtDraw.top, m_rtDraw.right, m_rtDraw.bottom, dwMaskColor);
	return true;
}
void KObject::Set(KPoint pos)
{
	m_pos.x = pos.x;
	m_pos.y = pos.y;
}
void KObject::Set(float x, float y, DWORD l, DWORD t, DWORD r, DWORD b)
{
	m_pos.x = x;
	m_pos.y = y;
	m_rtDraw.left = l;
	m_rtDraw.right = r;
	m_rtDraw.bottom = b;
	m_rtDraw.top = t;
}
bool KObject::Init()
{
	return true;
}
bool KObject::Frame()
{
	if (I_KInput.getKey('A'))
	{
		m_pos.x += (-1 * g_fSecPerFrame * 200.0f);
	}
	if (I_KInput.getKey('D'))
	{
		m_pos.x += (1 * g_fSecPerFrame * 200.0f);
	}
	if (I_KInput.getKey('W'))
	{
		m_pos.y += (-1 * g_fSecPerFrame * 200.0f);
	}
	if (I_KInput.getKey('S'))
	{
		m_pos.y += (1 * g_fSecPerFrame * 200.0f);
	}
	if (I_KInput.getMouse(VK_MBUTTON) == KEY_PUSH)
	{
		MessageBox(nullptr, L"KEY_PUSH", L"LBUTTON", MB_OK);
	}
	return true;
}
bool KObject::Render()
{
	if (m_pMaskBitmap->m_hBitmap == nullptr)
	{
		BitBlt(g_hOffScreenDC, static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_rtDraw.right, m_rtDraw.bottom, m_pColorBitmap->m_hMemDC, m_rtDraw.left, m_rtDraw.top, SRCCOPY);
		return true;
	}
	BitBlt(g_hOffScreenDC, static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_rtDraw.right, m_rtDraw.bottom, m_pMaskBitmap->m_hMemDC, m_rtDraw.left, m_rtDraw.top, SRCAND);
	BitBlt(g_hOffScreenDC, static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_rtDraw.right, m_rtDraw.bottom, m_pColorBitmap->m_hMemDC, m_rtDraw.left, m_rtDraw.top, SRCINVERT);  // SRCINVERT = XOR
	BitBlt(g_hOffScreenDC, static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_rtDraw.right, m_rtDraw.bottom, m_pMaskBitmap->m_hMemDC, m_rtDraw.left, m_rtDraw.top, SRCINVERT);
	//47, 48, MemDC, 1 + (frame * 48), 0
	return true;
}
bool KObject::Release()
{
	return true;
}

KObject::KObject()
{
	m_pColorBitmap = nullptr;
	m_pMaskBitmap = nullptr;
	m_pos.x = 0;
	m_pos.y = 0;
}


KObject::~KObject()
{
}
