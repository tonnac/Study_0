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
	m_fAlpha = 255.0f;
	m_fAttackRadius = 200.0f;
}
KObject::~KObject()
{

}



bool KObject::AlphaBlendd(HDC dcDest, int x, int y, int cx, int cy,
	HDC dcSrc,
	HDC dcMaskSrc, int sx, int sy, int scx, int scy, int alpha, DWORD opMode, COLORREF rgbMask)
{
	BITMAPINFOHEADER BMI;
	// Fill in the header info.
	BMI.biSize = sizeof(BITMAPINFOHEADER);
	BMI.biWidth = cx;
	BMI.biHeight = cy;
	BMI.biPlanes = 1;
	BMI.biBitCount = 32;
	BMI.biCompression = BI_RGB;   // No compression
	BMI.biSizeImage = 0;
	BMI.biXPelsPerMeter = 0;
	BMI.biYPelsPerMeter = 0;
	BMI.biClrUsed = 0;           // Always use the whole palette.
	BMI.biClrImportant = 0;

	BYTE * pSrcBits;
	HBITMAP hbmSrc;
	// Create DIB section in shared memory
	hbmSrc = CreateDIBSection(dcSrc, (BITMAPINFO *)&BMI, DIB_RGB_COLORS, (void **)&pSrcBits, 0, 0l);

	BYTE * pDestBits;
	HBITMAP hbmDest;
	// Create DIB section in shared memory
	hbmDest = CreateDIBSection(dcDest, (BITMAPINFO *)&BMI, DIB_RGB_COLORS, (void **)&pDestBits, 0, 0l);


	BYTE * pMaskBits;
	HBITMAP hbmMask;
	// Create DIB section in shared memory
	hbmMask = CreateDIBSection(dcMaskSrc, (BITMAPINFO *)&BMI, DIB_RGB_COLORS, (void **)&pMaskBits, 0, 0l);

	HDC dc = CreateCompatibleDC(NULL);

	HBITMAP dcOld = (HBITMAP)SelectObject(dc, hbmSrc);

	if (!StretchBlt(dc, 0, 0, cx, cy, dcSrc, sx, sy, scx, scy, SRCCOPY))
		return false;

	dcOld = (HBITMAP)SelectObject(dc, hbmDest);
	if (!StretchBlt(dc, 0, 0, cx, cy, dcDest, x, y, cx, cy, SRCCOPY))
		return false;

	dcOld = (HBITMAP)SelectObject(dc, hbmMask);
	if (!StretchBlt(dc, 0, 0, cx, cy, dcMaskSrc, sx, sy, scx, scy, SRCCOPY))
		return false;

	SelectObject(dc, dcOld);
	DeleteDC(dc);


	int red = GetRValue(rgbMask);
	int green = GetGValue(rgbMask);
	int blue = GetBValue(rgbMask);

	for (int j = 0; j < cy; ++j)
	{
		LPBYTE pbDestRGB = (LPBYTE)&((DWORD*)pDestBits)[j * cx];
		LPBYTE pbSrcRGB = (LPBYTE)&((DWORD*)pSrcBits)[j * cx];
		LPBYTE pbMaskRGB = (LPBYTE)&((DWORD*)pMaskBits)[j * cx];

		for (int i = 0; i < cx; ++i)
		{
			if (pbMaskRGB[0] == blue &&
				pbMaskRGB[1] == green &&
				pbMaskRGB[2] == red)
			{
				pbSrcRGB[0] = (pbDestRGB[0] * (255 - alpha) + pbSrcRGB[0] * alpha) >> 8;
				pbSrcRGB[1] = (pbDestRGB[1] * (255 - alpha) + pbSrcRGB[1] * alpha) >> 8;
				pbSrcRGB[2] = (pbDestRGB[2] * (255 - alpha) + pbSrcRGB[2] * alpha) >> 8;

			}
			else
			{
				pbSrcRGB[0] = pbDestRGB[0];
				pbSrcRGB[1] = pbDestRGB[1];
				pbSrcRGB[2] = pbDestRGB[2];
			}
			pbSrcRGB += 4;
			pbDestRGB += 4;
			pbMaskRGB += 4;
		}
	}

	dc = CreateCompatibleDC(NULL);

	SelectObject(dc, hbmSrc);
	if (!BitBlt(dcDest, x, y, cx, cy, dc, 0, 0, opMode))
		return false;
	DeleteDC(dc);

	DeleteObject(hbmSrc);
	DeleteObject(hbmDest);
	DeleteObject(hbmMask);
	return true;
}