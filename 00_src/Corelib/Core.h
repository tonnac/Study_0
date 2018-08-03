#pragma once
#include "WindowClass.h"
#include "Timer.h"
#include "Input.h"
#include "Bitmap.h"

class Core : public Window
{
protected:
	HDC				m_hScreenDC;
	HDC				m_hOffScreenDC;
	HBITMAP			m_hoffScreenBitmap;
	HBRUSH			m_hbrBack;
public:
	bool			GameInit();
	bool			GameRun();
	bool			GameRelease();
private:
	bool			GameFrame();
	bool			GameRender();
	bool			GamePreRender();
	bool			GamePostRender();
public:
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Relaese();
private:
	Timer m_Timer;
};