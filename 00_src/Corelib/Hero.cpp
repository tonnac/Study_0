#include "Hero.h"

Hero::Hero()
{

}
Hero::~Hero()
{

}

bool Hero::AlphaBlendd(HDC dcDest, int x, int y, int cx, int cy,
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

bool Hero::Render()
{
	m_fAlpha -= g_fSecPerFrame * 2000.0f;
	if (m_fAlpha < 0) m_fAlpha = 255.0f;

	//static BLENDFUNCTION blend;
	//blend.BlendOp = AC_SRC_OVER;
	//blend.BlendFlags = 0;
	//blend.SourceConstantAlpha = m_fAlpha;
	//blend.AlphaFormat = AC_SRC_OVER;	


	AlphaBlendd(g_hOffScreenDC,
		m_posDraw.x, m_posDraw.y,
		m_rtDraw.right, m_rtDraw.bottom,
		m_ColorBitmap->m_hMemDC,
		m_MaskBitmap->m_hMemDC,
		m_rtDraw.left,
		m_rtDraw.top,
		m_rtDraw.right,
		m_rtDraw.bottom,
		m_fAlpha);


//	return false;
	return true;
}