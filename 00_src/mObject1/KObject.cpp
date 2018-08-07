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
			static_cast<int>(m_posDraw.x + rtDraw.right), 
			static_cast<int>(m_posDraw.y),
			-rtDraw.right,rtDraw.bottom,
			m_ColorBitmap->m_hMemDC,
			m_rtDraw.left, m_rtDraw.top,
			m_rtDraw.right, m_rtDraw.bottom,
			SRCCOPY);
		break;
	case TB_ROTATION:
		StretchBlt(g_hOffScreenDC,
			static_cast<int>(m_posDraw.x),
			static_cast<int>(m_posDraw.y + rtDraw.bottom),
			rtDraw.right, -rtDraw.bottom,
			m_ColorBitmap->m_hMemDC,
			m_rtDraw.left, m_rtDraw.top,
			m_rtDraw.right, m_rtDraw.bottom,
			SRCCOPY);
		break;
	case LRTB_ROTATION:
		StretchBlt(g_hOffScreenDC,
			static_cast<int>(m_posDraw.x + rtDraw.right),
			static_cast<int>(m_posDraw.y + rtDraw.bottom),
			-rtDraw.right, -rtDraw.bottom,
			m_ColorBitmap->m_hMemDC,
			m_rtDraw.left, m_rtDraw.top,
			m_rtDraw.right, m_rtDraw.bottom,
			SRCCOPY);
		break;
	default:
		StretchBlt(g_hOffScreenDC,
			static_cast<int>(m_posDraw.x),
			static_cast<int>(m_posDraw.y),
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
		static_cast<int>(m_posDraw.x),
		static_cast<int>(m_posDraw.y),
		m_rtDraw.right, m_rtDraw.bottom,
		m_ColorBitmap->m_hMemDC,
		m_rtDraw.right, m_rtDraw.bottom,
		m_rtDraw.left, m_rtDraw.top,
		RGB(255,255,255));
	return true;
}

void KObject::Set(KPoint pos)
{
	m_posDraw = pos;
}
void KObject::Set(float x, float y, DWORD l, DWORD t, DWORD r, DWORD b)
{
	m_posDraw.x = x;
	m_posDraw.y = y;
	m_CenterPos.x = x + (r / 2);
	m_CenterPos.y = y + (b / 2);
	m_rtDraw.left = l;
	m_rtDraw.top = t;
	m_rtDraw.right = r;
	m_rtDraw.bottom = b;
	m_fDir[0] = (rand() % 2) ? 1.0f : -1.0f;   //¹æÇâ·£´ý
	m_fDir[1] = (rand() % 2) ? 1.0f : -1.0f;
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
		m_posDraw.x += (-1 * g_fSecPerFrame * 200.0f);
	}
	if (I_KInput.getKey('D'))
	{
		m_posDraw.x += (1 * g_fSecPerFrame * 200.0f);
	}
	if (I_KInput.getKey('W'))
	{
		m_posDraw.y += (-1 * g_fSecPerFrame * 200.0f);
	}
	if (I_KInput.getKey('S'))
	{
		m_posDraw.y += (1 * g_fSecPerFrame * 200.0f);
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
			static_cast<int>(m_posDraw.x),
			static_cast<int>(m_posDraw.y),
			m_rtDraw.right, m_rtDraw.bottom, 
			m_ColorBitmap->m_hMemDC, 
			m_rtDraw.left, m_rtDraw.top, 
			SRCCOPY);
		return true;
	}
	BitBlt(g_hOffScreenDC,
		static_cast<int>(m_posDraw.x),
		static_cast<int>(m_posDraw.y),
		m_rtDraw.right, m_rtDraw.bottom,
		m_MaskBitmap->m_hMemDC,
		m_rtDraw.left, m_rtDraw.top,
		SRCAND);
	BitBlt(g_hOffScreenDC,
		static_cast<int>(m_posDraw.x),
		static_cast<int>(m_posDraw.y),
		m_rtDraw.right, m_rtDraw.bottom,
		m_ColorBitmap->m_hMemDC,
		m_rtDraw.left, m_rtDraw.top,
		SRCINVERT);
	BitBlt(g_hOffScreenDC,
		static_cast<int>(m_posDraw.x),
		static_cast<int>(m_posDraw.y),
		m_rtDraw.right, m_rtDraw.bottom,
		m_MaskBitmap->m_hMemDC,
		m_rtDraw.left, m_rtDraw.top,
		SRCINVERT);
	// collision rect
	if (m_bDebugRect)
	{
		int prevMode = SetROP2(g_hOffScreenDC, R2_NOTMASKPEN);
		Rectangle(g_hOffScreenDC,
			static_cast<int>(m_posDraw.x),
			static_cast<int>(m_posDraw.y),
			m_posDraw.x + m_rtDraw.right,
			m_posDraw.y + m_rtDraw.bottom);
		SetROP2(g_hOffScreenDC, prevMode);
	}
	return true;
}
bool KObject::Release()
{
	return true;
}

KObject::KObject() : m_ColorBitmap(nullptr),m_MaskBitmap(nullptr), m_fSpeed(50.0f)
{
	m_posDraw.x = 0;
	m_posDraw.y = 0;
	m_fDir[0] = m_fDir[1] = 1.0f;
	m_bDebugRect = false;
}
KObject::~KObject()
{

}