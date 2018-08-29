#pragma once
#include "TWindow.h"
#include "TTimer.h"
#include "TSound.h"

class TCore : public TWindow
{
public:
	TTimer  m_Timer;
	HDC    m_hScreenDC;
	HDC    m_hOffScreenDC;
	HBITMAP m_hOffScreenBitmap;
	HBITMAP m_hOldOffBitmap;
	HBRUSH  m_hbrBack;
	HANDLE  m_hPen;
	bool	FrameShow;
public:
	bool	GameInit();
	bool	GameRun();
	bool	GameRelease();
	bool	GameFrame();
	bool	GameRender();
	bool	GamePreRender();
	bool	GamePostRender();
public:
	virtual bool	Init(){return true;}
	virtual bool	Frame(){return true;}
	virtual bool	Render(){return true;}
	virtual bool	Release(){return true;}
public:
	TCore();
	virtual ~TCore();
};

