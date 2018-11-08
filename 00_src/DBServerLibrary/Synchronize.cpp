#include "Synchronize.h"

Synchronize::Synchronize(ServerObj* serverObj) : mServerObj(serverObj)
{
	if (serverObj != nullptr)
		EnterCriticalSection(&mServerObj->getCS());
}
Synchronize::~Synchronize()
{
	if (mServerObj != nullptr)
		LeaveCriticalSection(&mServerObj->getCS());
}