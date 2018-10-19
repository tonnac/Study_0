#include "stdafx.h"
#include "Thread.h"

void Thread::CreateThread()
{
	m_hThread = _beginthreadex(NULL, 0, HandleRunner, this, 0, &m_iThreadID);
}
void Thread::Run()
{
	return;
}
unsigned int WINAPI Thread::HandleRunner(LPVOID Param)
{
	Thread * pThread = (Thread*)Param;
	if (pThread) pThread->Run();
	return 0;
}


Thread::Thread()
{
}
Thread::~Thread()
{
	CloseHandle((HANDLE)m_hThread);
}