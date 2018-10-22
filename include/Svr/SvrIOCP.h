#pragma once
#include "SvrObject.h"
#include "SvrStd.h"
#include "WorkThread.h"

class SvrIOCP : public Singleton<SvrIOCP>, public SvrObject
{
	friend class Singleton<SvrIOCP>;
public:
	SvrIOCP();
	virtual ~SvrIOCP();
public:
	WorkThread m_WorkerThread[WORKER_THREAD_COUNT];
	HANDLE m_hIOCP;
public:
	bool Init();
	void Add(HANDLE sock, ULONG_PTR Key);
};

#define I_IOCP SvrIOCP::getInst()