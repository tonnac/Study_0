#pragma once
#include "WindowClass.h"
#include "Timer.h"
#include "Input.h"

class Core : public Window
{
public:
	bool			GameInit();
	bool			GameRun();
	bool			GameRelease();
private:
	bool			GameFrame();
	bool			GameRender();
public:
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Relaese();
private:
	Timer m_Timer;
};