#include "KbkObject.h"

bool KbkObject::Frame()
{
	return true;
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




	static FLOAT fStep2 = 0.0f;
	fStep2 += g_fSecPerFrame * 200.0f;

	if (fStep2 >= m_rtDraw.bottom)
	{
		fStep2 = 0;
	}
	int iScroll2 = m_rtDraw.bottom - fStep2;

	//BitBlt(g_hOffScreenDC,
	//	m_rtDraw.left,
	//	fStep,
	//	m_rtDraw.right, 
	//	m_rtDraw.bottom - fStep,
	//	m_ColorBitmap->m_hMemDC,
	//	m_rtDraw.left, 
	//	m_rtDraw.top,
	//	SRCCOPY);
	//BitBlt(g_hOffScreenDC,
	//	m_rtDraw.left,
	//	m_rtDraw.top,
	//	m_rtDraw.right, 
	//	fStep,
	//	m_ColorBitmap->m_hMemDC,
	//	m_rtDraw.left, 
	//	iScroll,
	//	SRCCOPY);

	///////////////////////////////////////////////////////////////

	BitBlt(g_hOffScreenDC,
		m_rtDraw.left,
		fStep2,
		m_rtDraw.right,
		m_rtDraw.bottom + fStep2,
		m_ColorBitmap->m_hMemDC,
		m_rtDraw.left,
		m_rtDraw.top,
		SRCCOPY);
	BitBlt(g_hOffScreenDC,
		m_rtDraw.left,
		m_rtDraw.top,
		m_rtDraw.right,
		fStep2,
		m_ColorBitmap->m_hMemDC,
		m_rtDraw.left,
		iScroll2,
		SRCCOPY);
	return true;
}

bool KbkObject::Render()
{
	RenderScroll();
	return true;
}