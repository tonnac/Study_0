#include "Bitmap.h"

bool Bitmap::Load(T_STR szLoadFile)
{
	HDC hdc = GetDC(g_hWnd);
	m_hBitmap = static_cast<HBITMAP>(LoadImage(g_hInstance,
		szLoadFile.c_str(),
		IMAGE_BITMAP,
		0,
		0,
		LR_DEFAULTSIZE | LR_LOADFROMFILE));
	if (m_hBitmap != nullptr)
	{
		GetObject(m_hBitmap, sizeof(BITMAP), &m_bmpInfo);	// 비트맵 정보
		m_hMemDC = CreateCompatibleDC(hdc);					// DC안엔 여러가지를 담을수있다
		SelectObject(m_hMemDC, m_hBitmap);		
		m_szName = szLoadFile;
		ReleaseDC(g_hWnd, hdc);
		return true;
	}
	return false;
}

T_STR Bitmap::getName()
{
	return m_szName;
}
bool Bitmap::Init()
{
	return true;
}
bool Bitmap::Frame()
{
	return true;
}
bool Bitmap::Render()
{
	return true;
}
bool Bitmap::Release()
{
	return true;
}

Bitmap::Bitmap()
{
}


Bitmap::~Bitmap()
{
}
