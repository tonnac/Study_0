#include "Thread.h"


Thread::Thread()
{

}
Thread::~Thread()
{
	CloseHandle(mhThread);
}

HANDLE Thread::CreateThreadandRun()
{
	if (misStart) return nullptr;
	mhThread = (HANDLE)_beginthreadex(nullptr, 0, HandleRunner, this, 0, &miThreadID);
	misStart = true;
	return mhThread;
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