#include "Core.h"

bool Core::GameInit()
{
	m_Timer.Init();
	I_input.Init();
	Init();
	return true;
}
bool Core::GameRun()
{
	GameFrame();
	GameRender();
	return true;
}
bool Core::GameRelease()
{
	Relaese();
	m_Timer.Release();
	I_input.Release();
	return true;
}

bool Core::GameFrame()
{
	m_Timer.Frame();
	I_input.Frame();
	Frame();
	return true;
}
bool Core::GameRender()
{
	Render();
	m_Timer.Render();
	I_input.Render();
	return true;
}

bool Core::Init()
{
	return true;
}
bool Core::Frame()
{
	return true;
}
bool Core::Render()
{
	return true;
}
bool Core::Relaese()
{
	return true;
}