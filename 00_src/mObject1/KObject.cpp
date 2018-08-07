#include "KObject.h"

#pragma comment(lib,"msimg32.lib")

bool KObject::Draw(SHORT sType, RECT* rt)
{
	RECT rtDraw = m_rtDraw;
	if (rt != nullptr)
	{
		rtDraw = *rt;
	}
	switch (sType)
	{
	case LR_ROTATION:
		StretchBlt(g_hOffScreenDC,
			static_cast<int>(m_pos.x + rtDraw.right), 
			static_cast<int>(m_pos.y),
			-rtDraw.right,rtDraw.bottom,
			m_ColorBitmap->m_hMemDC,
			m_rtDraw.left, m_rtDraw.top,
			m_rtDraw.right, m_rtDraw.bottom,
			SRCCOPY);
		break;
	case TB_ROTATION:
		StretchBlt(g_hOffScreenDC,
			static_cast<int>(m_pos.x),
			static_cast<int>(m_pos.y + rtDraw.bottom),
			rtDraw.right, -rtDraw.bottom,
			m_ColorBitmap->m_hMemDC,
			m_rtDraw.left, m_rtDraw.top,
			m_rtDraw.right, m_rtDraw.bottom,
			SRCCOPY);
		break;
	case LRTB_ROTATION:
		StretchBlt(g_hOffScreenDC,
			static_cast<int>(m_pos.x + rtDraw.right),
			static_cast<int>(m_pos.y + rtDraw.bottom),
			-rtDraw.right, -rtDraw.bottom,
			m_ColorBitmap->m_hMemDC,
			m_rtDraw.left, m_rtDraw.top,
			m_rtDraw.right, m_rtDraw.bottom,
			SRCCOPY);
		break;
	default:
		StretchBlt(g_hOffScreenDC,
			static_cast<int>(m_pos.x),
			static_cast<int>(m_pos.y),
			rtDraw.right, rtDraw.bottom,
			m_ColorBitmap->m_hMemDC,
			m_rtDraw.left, m_rtDraw.top,
			m_rtDraw.right, m_rtDraw.bottom,
			SRCCOPY);
	}
	return true;
}
bool KObject::DrawColorKey(DWORD)
{
	TransparentBlt(g_hOffScreenDC,
		static_cast<int>(m_pos.x),
		static_cast<int>(m_pos.y),
		m_rtDraw.right, m_rtDraw.bottom,
		m_ColorBitmap->m_hMemDC,
		m_rtDraw.right, m_rtDraw.bottom,
		m_rtDraw.left, m_rtDraw.top,
		RGB(255,255,255));
	return true;
}

void KObject::Set(KPoint pos)
{
	m_pos = pos;
}
void KObject::Set(float x, float y, DWORD l, DWORD t, DWORD r, DWORD b)
{
	m_pos.x = x;
	m_pos.y = y;
	m_rtDraw.left = l;
	m_rtDraw.top = t;
	m_rtDraw.right = r;
	m_rtDraw.bottom = b;
}

bool KObject::LoadFile(const TCHAR* szColorFile, const TCHAR* szMaskFile)
{
	int index = I_BitmapMgr.Load(szColorFile);
	m_ColorBitmap = I_BitmapMgr.getPtr(index);
	assert(m_ColorBitmap != nullptr);
	if (szMaskFile != nullptr)
	{
		index = I_BitmapMgr.Load(szMaskFile);
		m_MaskBitmap = I_BitmapMgr.getPtr(index);
	}
	return true;
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
	if (m_MaskBitmap == nullptr)
	{
		BitBlt(g_hOffScreenDC, 
			static_cast<int>(m_pos.x), 
			static_cast<int>(m_pos.y),
			m_rtDraw.right, m_rtDraw.bottom, 
			m_ColorBitmap->m_hMemDC, 
			m_rtDraw.left, m_rtDraw.top, 
			SRCCOPY);
		return true;
	}
	BitBlt(g_hOffScreenDC,
		static_cast<int>(m_pos.x),
		static_cast<int>(m_pos.y),
		m_rtDraw.right, m_rtDraw.bottom,
		m_MaskBitmap->m_hMemDC,
		m_rtDraw.left, m_rtDraw.top,
		SRCAND);
	BitBlt(g_hOffScreenDC,
		static_cast<int>(m_pos.x),
		static_cast<int>(m_pos.y),
		m_rtDraw.right, m_rtDraw.bottom,
		m_ColorBitmap->m_hMemDC,
		m_rtDraw.left, m_rtDraw.top,
		SRCINVERT);
	BitBlt(g_hOffScreenDC,
		static_cast<int>(m_pos.x),
		static_cast<int>(m_pos.y),
		m_rtDraw.right, m_rtDraw.bottom,
		m_MaskBitmap->m_hMemDC,
		m_rtDraw.left, m_rtDraw.top,
		SRCINVERT);
	return true;
}
bool KObject::Release()
{
	return true;
}

KObject::KObject() : m_ColorBitmap(nullptr),m_MaskBitmap(nullptr)
{
	m_pos.x = 0;
	m_pos.y = 0;
}
KObject::~KObject()
{

}