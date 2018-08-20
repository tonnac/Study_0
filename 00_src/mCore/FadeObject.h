#pragma once
#include "Object.h"

class FadeObject : public Object
{
public:
	~FadeObject();
public:
	virtual bool		Init();
	virtual bool		Frame();
	virtual bool		Render();
	virtual bool		Release();
private:
	BLENDFUNCTION		m_bBlend;
	FLOAT				m_fAlpha;
	HDC					m_hMemDC;
	HBRUSH				m_bkBrush;
	HBITMAP				m_hOffBitmap;
};