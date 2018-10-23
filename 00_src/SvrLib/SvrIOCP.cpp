#include "stdafx.h"
#include "SvrIOCP.h"


SvrIOCP::SvrIOCP()
{}
SvrIOCP::~SvrIOCP()
{}

bool SvrIOCP::Init()
{
	m_hIOCP = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, WORKER_THREAD_COUNT);

	for (int iThread = 0; iThread < WORKER_THREAD_COUNT; ++iThread)
	{
		m_WorkerThread[iThread].CreateThread();
	}
	return true;
}
void SvrIOCP::Add(HANDLE sock, ULONG_PTR Key)
{
	CreateIoCompletionPort(sock, m_hIOCP, Key, WORKER_THREAD_COUNT);
}