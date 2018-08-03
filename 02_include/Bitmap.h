#pragma once
#include "Std.h"

class Bitmap
{
public:
	bool			Load(T_STR szLoadFile);
	T_STR			getName();
public:
	bool			Init();
	bool			Frame();
	bool			Render();
	bool			Release();
public:
	Bitmap();
	virtual			~Bitmap();
public:
	T_STR			m_szName;
	HDC				m_hMemDC;
	HBITMAP			m_hBitmap;
	BITMAP			m_bmpInfo;
};