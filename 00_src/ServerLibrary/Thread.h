#pragma once
#include "ServerObj.h"

class Thread : public ServerObj
{
public:
	Thread();
	virtual ~Thread();
public:
	void CreateThread();
	virtual bool Run();
	static UINT WINAPI HandleRunner(LPVOID arg);
protected:
	UINT mhThread	= 0;
	UINT miThreadID = 0;
	bool misStart	= false;
};