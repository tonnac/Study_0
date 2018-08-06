#pragma once
#include "Core.h"

class KObject
{
	KPoint					m_pos;
	Bitmap					m_ColorBitmap;
	Bitmap					m_MaskBitmap;
	RECT					m_rtDraw;
public:
	virtual bool			Load(const TCHAR*);
	bool					Draw(DWORD);
	virtual void			Set(KPoint);
	virtual void			Set(float, float, DWORD,DWORD,DWORD,DWORD);
	virtual bool			Init();
	virtual bool			Frame();
	virtual bool			Render();
	virtual bool			Release();
public:
							KObject();
	virtual					~KObject();
};