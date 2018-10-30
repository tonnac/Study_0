#include "IOCP.h"
#include "Server.h"

WorkerThread::WorkerThread()
{

}
WorkerThread::~WorkerThread()
{
	EnterCriticalSection(&SrvUtil::mCs);
	std::vector<std::string>::iterator iter;
	iter = std::find(SrvUtil::mThreadName.begin(), SrvUtil::mThreadName.end(), std::string("WorkerThread"));
	if (iter != SrvUtil::mThreadName.end())
		SrvUtil::mThreadName.erase(iter);
	LeaveCriticalSection(&SrvUtil::mCs);
}

HANDLE WorkerThread::CreateThreadandRun()
{
	EnterCriticalSection(&SrvUtil::mCs);
	SrvUtil::mThreadName.push_back("WorkerThread");
	LeaveCriticalSection(&SrvUtil::mCs);
	if (misStart) return nullptr;
	mhThread = (HANDLE)_beginthreadex(nullptr, 0, HandleRunner, this, CREATE_SUSPENDED, &miThreadID);
	misStart = true;
	return mhThread;
}

void WorkerThread::setHandle(const HANDLE& handle)
{
	mhComport = handle;
}

bool WorkerThread::Run()
{
	LPOVERLAPPEDEX lpOverlapped = nullptr;
	User* pUser = nullptr;
	DWORD Trans;
	while (1)
	{
		BOOL ret = GetQueuedCompletionStatus(mhComport, &Trans, (PULONG_PTR)&pUser, (LPOVERLAPPED*)&lpOverlapped, INFINITE);
		if (isExit == true)
		{
			break;
		}
		if (pUser == nullptr)
		{
			continue;
		}

		if (ret == TRUE && Trans != 0 && lpOverlapped != nullptr)
		{
			pUser->Dispatch(Trans, lpOverlapped);
		}
		else
		{
			if (pUser != nullptr && GetLastError() != ERROR_OPERATION_ABORTED)
			{
				if (Trans == 0)
				{
					if (ret == FALSE)
					{
						S_Server->RemoveUser(pUser);
						continue;
					}
				}
			}
		}
		S_Server->ProcessPacket();
	}
	return true;
}

IOCP::IOCP()
{

}
IOCP::~IOCP()
{
	
}

void IOCP::Initialize()
{
	mhComport = CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0, 0);
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	mNumofProcess = sysinfo.dwNumberOfProcessors;

	for (DWORD i = 0; i < mNumofProcess; ++i)
	{
		WorkerPtr workthread = std::make_shared<WorkerThread>();
		workthread->setHandle(mhComport);
		HANDLE handle = workthread->CreateThreadandRun();
		miocpThread.mThreadHandle.push_back(handle);
		miocpThread.mWorkerthread.push_back(std::move(workthread));
	}
}
void IOCP::AddUser(const User* user)
{
	CreateIoCompletionPort((HANDLE)user->mUserSock, mhComport, (ULONG_PTR)user, 0);
}
bool IOCP::Run()
{
	size_t ThreadNum = miocpThread.mWorkerthread.size();
	for (size_t i = 0; i < ThreadNum; ++i)
	{
		ResumeThread(miocpThread.mThreadHandle[i]);
	}
	return true;
}
void IOCP::Release()
{
	CloseHandle(mhComport);
	WaitForMultipleObjects(mNumofProcess, miocpThread.mThreadHandle.data(), TRUE, INFINITE);
	miocpThread.mWorkerthread.clear();
}