#include "TBkObj.h"

bool TBkObj::FadeOut()
{
	static float fAlpha = 255;
	fAlpha -= g_fSecPerFrame * 30;
	if (fAlpha < 0) return true;

	static BLENDFUNCTION blend;
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = fAlpha;
	blend.AlphaFormat = AC_SRC_OVER;

	::AlphaBlend(g_hOffScreenDC,
		m_posDraw.x, m_posDraw.y,
		m_rtDraw.right, m_rtDraw.bottom,
		m_pColorBitmap->m_hMemDC,
		m_rtDraw.left,
		m_rtDraw.top,
		m_rtDraw.right,
		m_rtDraw.bottom,
		blend);
	return false;
}
bool TBkObj::FadeIn()
{
	static float fAlpha = 0;
	fAlpha += g_fSecPerFrame * 30;
	if (fAlpha > 255) return true;

	static BLENDFUNCTION blend;
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = fAlpha;
	blend.AlphaFormat = AC_SRC_OVER;

	::AlphaBlend(g_hOffScreenDC,
		m_posDraw.x, m_posDraw.y,
		m_rtDraw.right, m_rtDraw.bottom,
		m_pColorBitmap->m_hMemDC,
		m_rtDraw.left,
		m_rtDraw.top,
		m_rtDraw.right,
		m_rtDraw.bottom,
		blend);
	return false;
}
bool TBkObj::Frame()
{
	return true;
}
bool	TBkObj::RenderScrool()
{
	static float fStep = 0.0f;
	fStep += g_fSecPerFrame * m_fScroolSpeed;
	if (fStep >= m_pColorBitmap->m_bmpInfo.bmHeight) fStep = 0;
	int iScrool = m_pColorBitmap->m_bmpInfo.bmHeight - fStep;

	BitBlt(g_hOffScreenDC,
		m_posDraw.x, fStep,
		m_rtDraw.right,
		m_rtDraw.bottom- fStep,
		m_pColorBitmap->m_hMemDC,
		m_rtDraw.left,
		m_rtDraw.top, SRCCOPY);
	BitBlt(g_hOffScreenDC,
		m_posDraw.x, m_posDraw.y,
		m_rtDraw.right,
		fStep,
		m_pColorBitmap->m_hMemDC,
		m_rtDraw.left,
		iScrool, SRCCOPY);	
	return true;
}
bool	TBkObj::Render()
{
	if (FadeIn())
		RenderScrool();	
	return true;
}
TBkObj::TBkObj()
{
	m_fScroolSpeed = 100.0f;
}


TBkObj::~TBkObj()
{
}
