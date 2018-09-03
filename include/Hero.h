#pragma once
#include "KObject.h"

class Hero : public KObject
{
public:
	Hero();
	virtual ~Hero();
public:
	bool			Render	() override;
	bool AlphaBlendd(HDC dcDest, int x, int y, int cx, int cy,
		HDC dcSrc,
		HDC dcMaskSrc, int sx, int sy, int scx, int scy, int alpha, DWORD opMode = SRCCOPY, COLORREF rgbMask = RGB(0,0,0));
private:
};