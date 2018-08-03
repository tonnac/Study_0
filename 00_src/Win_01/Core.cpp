#include "Core.h"

bool Core::GameInit()
{
	m_Timer.Init();
	return true;
}
bool Core::GameRun()
{
	m_Timer.Frame();
	m_Timer.Render();
	return true;
}
bool Core::GameRelease()
{
	m_Timer.Release();
	return true;
}