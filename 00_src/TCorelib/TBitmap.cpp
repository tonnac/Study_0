#include "TBitmap.h"

bool	TBitmap::Load(T_STR szLoadFile)
{
	HDC hdc = GetDC(g_hWnd);
	m_hBitmap = (HBITMAP)LoadImage(g_hInstance,
		szLoadFile.c_str(), 
		IMAGE_BITMAP, 0, 0, 
		LR_DEFAULTSIZE | LR_LOADFROMFILE );

	if (m_hBitmap != NULL)
	{		
		GetObject(m_hBitmap, sizeof(BITMAP),&m_bmpInfo );
		m_hMemDC = CreateCompatibleDC(hdc);
		SelectObject(m_hMemDC, m_hBitmap);
		m_szName = szLoadFile;
		ReleaseDC(g_hWnd, hdc);
		return true;
	}
	ReleaseDC(g_hWnd, hdc);
	return false;
};

bool	TBitmap::Init()	
{
	return true;
}
bool	TBitmap::Frame() 
{
	return true;
}
bool	TBitmap::Render() 
{	
	return true;
}
bool	TBitmap::Release() 
{
	DeleteObject(m_hBitmap);
	ReleaseDC(g_hWnd, m_hMemDC);
	return true;
}

TBitmap::TBitmap()
{
}


TBitmap::~TBitmap()
{
}
