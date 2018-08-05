#pragma once
#include "Std.h"

class Bitmap
{
public:
	bool			Init();
	bool			Frame();
	bool			Render();
	bool			Release();
	bool			LoadFile(T_STR);
public:
	T_STR			getName() const;
	HDC				getMemDC() const;
private:
	T_STR			m_szName;
	HDC				m_hMemDC;
	HBITMAP			m_hBitmap;
	BITMAP			m_bBmpInfo;
};