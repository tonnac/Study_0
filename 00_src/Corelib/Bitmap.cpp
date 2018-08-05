#include "Bitmap.h"

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
	DeleteDC(m_hMemDC);
	DeleteObject(m_hBitmap);
	return true;
}
bool Bitmap::LoadFile(T_STR szLoadFile)
{
	HDC hdc = GetDC(g_hWnd);
	m_hBitmap = static_cast<HBITMAP>(LoadImage(g_hInstance, szLoadFile.c_str(),
		IMAGE_BITMAP,
		0, 0,
		LR_DEFAULTSIZE | LR_LOADFROMFILE));
	if (m_hBitmap == nullptr)
	{
		return false;
	}
	GetObject(m_hBitmap, sizeof(BITMAP), &m_bBmpInfo);
	m_szName = szLoadFile;
	m_hMemDC = CreateCompatibleDC(g_hOffScreenDC);
	SelectObject(m_hMemDC, m_hBitmap);

	ReleaseDC(g_hWnd, hdc);
	return true;
}
T_STR Bitmap::getName() const
{
	return m_szName;
}
HDC Bitmap::getMemDC() const
{
	return m_hMemDC;
}