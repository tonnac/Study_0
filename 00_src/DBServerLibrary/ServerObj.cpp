#include "ServerObj.h"

ServerObj::ServerObj()
{
	InitializeCriticalSection(&mCs);
}
ServerObj::~ServerObj()
{
	DeleteCriticalSection(&mCs);
}

CRITICAL_SECTION& ServerObj::getCS()
{
	return mCs;
}