#pragma once
#include "Timer.h"
#include "Win_01.h"

class Core : public Window
{
public:
	bool GameInit();
	bool GameRun();
	bool GameRelease();
private:
	Timer m_Timer;
};