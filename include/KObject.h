#pragma once
#include "Core.h"
#include "BitmapMgr.h"
#include "Collision.h"

#define LR_ROTATION		0x01
#define TB_ROTATION		0x02
#define LRTB_ROTATION   0x04


class KObject
{
private:
	float				Diff;
	float				Angle;
	HDC					RotaDC;
	HDC					MaskDC;
	HDC					ColorDC;
	HBRUSH				bkBrush;
	HBITMAP				ColorBit;
	HBITMAP				MaskBit;
public:
	KPoint				m_CenterPos;
	KPoint				m_posDraw;
	Bitmap*				m_ColorBitmap;
	Bitmap*				m_MaskBitmap;
	float				m_fDir[2];
	float				m_fSpeed;
	bool				m_bDead;
public:
	bool				m_bDebugRect;
public:
	RECT				m_rtDraw;
	RECT				m_rtCollision;
public:
	virtual bool		Draw(SHORT, RECT* = 0);
	virtual bool		DrawColorKey(DWORD);
	virtual void		Set(KPoint);
	virtual void		Set(float, float, DWORD, DWORD, DWORD, DWORD);
	virtual bool		LoadFile(const TCHAR*, const TCHAR* = 0);
	virtual bool		Init();
	virtual bool		Frame();
	virtual bool		Render();
	virtual bool		Release();
public:
	void	RotationBlt(float fAngle);
	void	GetRotationBimap(float fAngle, HBITMAP hBitmap,	Bitmap* pSrcBitmap);
public:
	KObject();
	virtual ~KObject();
};