#include "KObject.h"

//#pragma comment(lib,"msimg32,lib")

bool KObject::Load(const TCHAR* pszFileName)
{
	m_ColorBitmap.LoadFile(pszFileName);
	return true;
}
bool KObject::Draw(DWORD dwMaskColor)
{
	HDC MemDC = m_ColorBitmap.getMemDC();
//	TransparentBlt(g_hOffScreenDC, static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_rtDraw.right, m_rtDraw.bottom, MemDC, m_rtDraw.left, m_rtDraw.top, m_rtDraw.right, m_rtDraw.bottom, dwMaskColor);
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
	m_ColorBitmap.Init();
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
	m_ColorBitmap.Frame();
	return true;
}
bool KObject::Render()
{
	HDC MemDC = m_ColorBitmap.getMemDC();
	//	Sleep(10);
	// TransparentBlt(g_hOffScreenDC, static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_rtDraw.right, m_rtDraw.bottom, MemDC, m_rtDraw.left, m_rtDraw.top, m_rtDraw.right, m_rtDraw.bottom,RGB(255,255,255));  쓰지말자하
	BitBlt(g_hOffScreenDC, static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_rtDraw.right, m_rtDraw.bottom, MemDC, m_rtDraw.left, m_rtDraw.top, SRCCOPY);
	//47, 48, MemDC, 1 + (frame * 48), 0
	return m_ColorBitmap.Render();
}
bool KObject::Release()
{
	return m_ColorBitmap.Release();
}

KObject::KObject()
{
	m_pos.x = 0;
	m_pos.y = 0;
}


KObject::~KObject()
{
}
