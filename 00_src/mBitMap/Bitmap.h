#pragma once
#include "Std.h"


class Bitmap
{
public:
	bool			Init();
	bool			Frame();
	bool			Render();
	bool			Release();
public:
	bool			LoadFile(T_STR);
public:
	HDC				m_hMemDC;
	BITMAP			m_bBitInfo;
	HBITMAP			m_hBitmap;
	T_STR			szFilename;
};