#include "Bitmap.h"

bool Bitmap::LoadFile(T_STR szLoadFile)
{
	HDC hdc = GetDC(g_hWnd);
	m_hBitmap = static_cast<HBITMAP>(LoadImage(g_hInstance,
		szLoadFile.c_str(),
		IMAGE_BITMAP,
		0,
		0,
		LR_DEFAULTSIZE | LR_LOADFROMFILE));
	if (m_hBitmap == nullptr)
	{
		return false;
	}
	GetObject(m_hBitmap, sizeof(BITMAP), &m_bBitInfo);	
	m_hMemDC = CreateCompatibleDC(hdc);					
	SelectObject(m_hMemDC, m_hBitmap);
	szFilename = szLoadFile;
	ReleaseDC(g_hWnd, hdc);
	return true;
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