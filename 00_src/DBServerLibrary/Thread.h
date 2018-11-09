#pragma once
#include "ServerObj.h"

class Thread : public ServerObj
{
public:
	Thread();
	virtual ~Thread();
public:
	virtual HANDLE CreateThreadandRun();
	static UINT WINAPI HandleRunner(LPVOID arg);
protected:
	virtual bool Run();
protected:
	HANDLE mhThread	= 0;
	UINT miThreadID = 0;
	bool misStart	= false;
};