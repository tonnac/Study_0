#include "KbkObject.h"

bool KbkObject::Frame()
{
	return true;
}
bool KbkObject::FadeOut()
{
	static FLOAT fAlpha = 255.0f;
	fAlpha -= g_fSecPerFrame * 50.0f;
	if (fAlpha < 0) return true;

	static BLENDFUNCTION blend;
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = fAlpha;
	blend.AlphaFormat = AC_SRC_OVER;


	::AlphaBlend(g_hOffScreenDC,
		m_posDraw.x,
		m_posDraw.x,
		m_rtDraw.right,
		m_rtDraw.bottom,
		m_ColorBitmap->m_hMemDC,
		m_rtDraw.left,
		m_rtDraw.top,
		m_rtDraw.right,
		m_rtDraw.bottom,
		blend);


	return false;
}
bool KbkObject::FadeIn()
{
	static FLOAT fAlpha1 = 0.0f;
	fAlpha1 += g_fSecPerFrame * 50.0f;
	if (fAlpha1 > 255) return true;

	static BLENDFUNCTION blend;
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = fAlpha1;
	blend.AlphaFormat = AC_SRC_OVER;


	AlphaBlend(g_hOffScreenDC,
		m_posDraw.x,
		m_posDraw.y,
		m_rtDraw.right,
		m_rtDraw.bottom,
		m_ColorBitmap->m_hMemDC,
		m_rtDraw.left,
		m_rtDraw.top,
		m_rtDraw.right,
		m_rtDraw.bottom,
		blend);


	return false;
}
bool KbkObject::RenderScroll()
{
	static FLOAT fStep = 0.0f;
	fStep += g_fSecPerFrame * m_fScrollSpeed;

	if (fStep >= m_ColorBitmap->m_bBmpInfo.bmHeight)
	{
		fStep = 0;
	}
	int iScroll = m_ColorBitmap->m_bBmpInfo.bmHeight - fStep;

	BitBlt(g_hOffScreenDC,
		m_rtDraw.left,
		fStep,
		m_rtDraw.right, 
		m_rtDraw.bottom - fStep,
		m_ColorBitmap->m_hMemDC,
		m_rtDraw.left, 
		m_rtDraw.top,
		SRCCOPY);
	BitBlt(g_hOffScreenDC,
		m_rtDraw.left,
		m_rtDraw.top,
		m_rtDraw.right, 
		fStep,
		m_ColorBitmap->m_hMemDC,
		m_rtDraw.left, 
		iScroll,
		SRCCOPY);

	///////////////////////////////////////////////////////////////

	//BitBlt(g_hOffScreenDC,
	//	m_rtDraw.left,
	//	fStep2,
	//	m_rtDraw.right,
	//	m_rtDraw.bottom + fStep2,
	//	m_ColorBitmap->m_hMemDC,
	//	m_rtDraw.left,
	//	m_rtDraw.top,
	//	SRCCOPY);
	//BitBlt(g_hOffScreenDC,
	//	m_rtDraw.left,
	//	m_rtDraw.top,
	//	m_rtDraw.right,
	//	fStep2,
	//	m_ColorBitmap->m_hMemDC,
	//	m_rtDraw.left,
	//	iScroll2,
	//	SRCCOPY);



	return true;
}
bool KbkObject::Render()
{
	if (FadeIn())
	{
		RenderScroll();
	}
	//else
	//	KObject::Render();
	return true;
}