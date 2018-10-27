#include "Thread.h"


Thread::Thread()
{

}
Thread::~Thread()
{
	CloseHandle((HANDLE)mhThread);
}

void Thread::CreateThread()
{
	if (misStart) return;
	mhThread = _beginthreadex(nullptr, 0, HandleRunner, this, 0, &miThreadID);
	misStart = true;
}
bool Thread::Run()
{
	return true;
}
UINT WINAPI Thread::HandleRunner(LPVOID arg)
{
	Thread* thread = (Thread*)arg;
	if (thread != nullptr) thread->Run();
	return 0;
}