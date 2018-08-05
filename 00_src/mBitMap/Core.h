#pragma once
#include "WindowClass.h"
#include "Timer.h"
#include "Input.h"
#include "Bitmap.h"

class KCore : public KWindow
{
public:
	virtual	bool				GameInit();
	virtual	bool				GameFrame();
	virtual bool				GameRender();
	virtual bool				GameRelease();
public:
	virtual bool				Init();
	virtual bool				Frame();
	virtual bool				Render();
	virtual bool				Release();
private:
	bool						GamePreRender();
	bool						GamePostRender();
private:
	KTimer						m_Timer;
private:
	HDC							m_hOnScreenDC;
	HDC							m_hOffScreenDC;
	HBITMAP						m_hOffBitmap;
	HBRUSH						m_hBkColor;
};