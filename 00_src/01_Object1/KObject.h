#pragma once
#include "Core.h"
#include "BitmapMgr.h"

#define LR_ROTATION 0x01
#define TB_ROTATION 0x02
#define LRTB_ROTATION 0x04

class KObject
{
	KPoint					m_pos;
	Bitmap*					m_pColorBitmap;
	Bitmap*					m_pMaskBitmap;
public:
	RECT					m_rtDraw;
public:
	virtual bool			Load(const TCHAR*, const TCHAR* =0);
	virtual bool			Draw(SHORT, RECT* =0);
	virtual bool			DrawColorKey(DWORD);
	virtual void			Set(KPoint);
	virtual void			Set(float, float, DWORD, DWORD, DWORD, DWORD);
	virtual bool			Init();
	virtual bool			Frame();
	virtual bool			Render();
	virtual bool			Release();
public:
							KObject();
	virtual					~KObject();
};