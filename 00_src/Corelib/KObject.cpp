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
	m_CenterPos.x = x;
	m_CenterPos.y = y;
	m_posDraw.x = x - (r / 2);
	m_posDraw.y = y - (b / 2);
	
	m_rtDraw.left = l;
	m_rtDraw.top = t;
	m_rtDraw.right = r;
	m_rtDraw.bottom = b;
	m_fDir[0] = (rand() % 2) ? 1.0f : -1.0f;   //¹æÇâ·£´ý
	m_fDir[1] = (rand() % 2) ? 1.0f : -1.0f;


	Diff = sqrt(((m_rtDraw.right) * (m_rtDraw.right) + (m_rtDraw.bottom) * (m_rtDraw.bottom)));

	RotaDC = CreateCompatibleDC(g_hOnScreenDC);
	MaskDC = CreateCompatibleDC(g_hOnScreenDC);
	ColorDC = CreateCompatibleDC(g_hOnScreenDC);

	ColorBit = CreateCompatibleBitmap(g_hOnScreenDC, Diff, Diff);
	MaskBit = CreateCompatibleBitmap(g_hOnScreenDC, Diff, Diff);
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
	Angle = 0.0f;
	bkBrush = CreateSolidBrush(RGB(255, 255, 255));
	return true;
}
bool KObject::Frame()
{
	if (I_KInput.getKey('A'))
	{
		m_CenterPos.x += (-1 * g_fSecPerFrame * 200.0f);
	}
	if (I_KInput.getKey('D'))
	{
		m_CenterPos.x += (1 * g_fSecPerFrame * 200.0f);
	}
	if (I_KInput.getKey('W'))
	{
		m_CenterPos.y += (-1 * g_fSecPerFrame * 200.0f);
	}
	if (I_KInput.getKey('S'))
	{
		m_CenterPos.y += (1 * g_fSecPerFrame * 200.0f);
	}
	if (I_KInput.getMouse(VK_MBUTTON) == KEY_PUSH)
	{
		MessageBox(nullptr, L"KEY_PUSH", L"LBUTTON", MB_OK);
	}
	m_posDraw.x = m_CenterPos.x - (m_rtDraw.right / 2);
	m_posDraw.y = m_CenterPos.y - (m_rtDraw.bottom / 2);
	m_rtCollision.left = m_posDraw.x;
	m_rtCollision.top = m_posDraw.y;
	m_rtCollision.right = m_rtCollision.left + m_rtDraw.right;
	m_rtCollision.bottom = m_rtCollision.top + m_rtDraw.bottom;
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
		int prevMode = SetROP2(g_hOffScreenDC, R2_XORPEN);
		Rectangle(g_hOffScreenDC,
			static_cast<int>(m_rtCollision.left),
			static_cast<int>(m_rtCollision.top),
			static_cast<int>(m_rtCollision.right),
			static_cast<int>(m_rtCollision.bottom));
		SetROP2(g_hOffScreenDC, prevMode);
		
	}
	return true;
}
bool KObject::Release()
{

	DeleteDC(RotaDC);
	DeleteDC(MaskDC);
	DeleteDC(ColorDC);
	DeleteObject(bkBrush);
	DeleteObject(ColorBit);
	DeleteObject(MaskBit);
	return true;
}

void KObject::RotationBlt(float fAngle)
{
	GetRotationBimap(fAngle, MaskBit, m_MaskBitmap);
	GetRotationBimap(fAngle, ColorBit, m_ColorBitmap);
	HBITMAP omask = (HBITMAP)SelectObject(MaskDC, MaskBit);
	HBITMAP ocolor = (HBITMAP)SelectObject(ColorDC, ColorBit);
	BitBlt(g_hOffScreenDC,
		static_cast<int>(m_CenterPos.x - (Diff / 2)),
		static_cast<int>(m_CenterPos.y - (Diff / 2)),
		Diff,
		Diff,
		MaskDC,
		0, 0,
		SRCAND);
	BitBlt(g_hOffScreenDC,
		static_cast<int>(m_CenterPos.x - (Diff / 2)),
		static_cast<int>(m_CenterPos.y - (Diff / 2)),
		Diff,
		Diff,
		ColorDC,
		0, 0,
		SRCINVERT);
	BitBlt(g_hOffScreenDC,
		static_cast<int>(m_CenterPos.x - (Diff / 2)),
		static_cast<int>(m_CenterPos.y - (Diff / 2)),
		Diff,
		Diff,
		MaskDC,
		0, 0,
		SRCINVERT);
	SelectObject(MaskDC, omask);
	SelectObject(ColorDC, ocolor);
}
void KObject::GetRotationBimap(float fAngle, HBITMAP hBitmap, Bitmap* pSrcBitmap)
{
	float rad = fAngle * 3.141592f / 180.0f;
	float fCosine = cos(rad);
	float fSine = sin(rad);

	HBRUSH hOldBrush = (HBRUSH)SelectObject(RotaDC, bkBrush);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(RotaDC, hBitmap);

	PatBlt(RotaDC, 0, 0, Diff, Diff, PATCOPY);

	int OldGraphic = SetGraphicsMode(RotaDC, GM_ADVANCED);

	XFORM xform1;

	xform1.eM11 = fCosine;		xform1.eM12 = fSine;
	xform1.eM21 = -fSine;		xform1.eM22 = fCosine;
	xform1.eDx = Diff / 2;		xform1.eDy = Diff / 2;

	SetWorldTransform(RotaDC, &xform1);

	BitBlt(RotaDC, -(m_rtDraw.right / 2), -(m_rtDraw.bottom / 2),
		m_rtDraw.right, m_rtDraw.bottom, pSrcBitmap->m_hMemDC, m_rtDraw.left, m_rtDraw.top, SRCCOPY);

	SelectObject(RotaDC, hOldBrush);
	SelectObject(RotaDC, hOldBitmap);

	xform1.eM11 = 1;		xform1.eM12 = 0;
	xform1.eM21 = 0;		xform1.eM22 = 1;
	xform1.eDx = 0;			xform1.eDy = 0;

	SetWorldTransform(RotaDC, &xform1);
	SetGraphicsMode(RotaDC, OldGraphic);

}

KObject::KObject() : m_ColorBitmap(nullptr),m_MaskBitmap(nullptr)
{
	m_posDraw.x = 0;
	m_posDraw.y = 0;
	m_fDir[0] = m_fDir[1] = 1.0f;
	m_bDebugRect = false;
	m_fSpeed = rand() % 150 + 70.f;
	m_bDead = false;
	m_fScrollSpeed = 100.0f;
}
KObject::~KObject()
{

}