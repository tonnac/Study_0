#pragma once
#include "SvrObject.h"

class Thread : public SvrObject
{
public:
	unsigned int m_hThread;
	unsigned int m_iThreadID;
public:
	void CreateThread();
	virtual void Run();
	static unsigned int WINAPI HandleRunner(LPVOID Param);
public:
	Thread();
	virtual ~Thread();
};