#pragma once
#include "ServerModel.h"

class Server;

class WorkerThread : public Thread
{
public:
	virtual HANDLE CreateThreadandRun() override;
	void setHandle(const HANDLE& handle);
private:
	bool Run() override;
private:
	HANDLE mhComport;
};

using WorkerPtr = std::shared_ptr<WorkerThread>;

struct IOCPThread
{
	std::vector<WorkerPtr> mWorkerthread;
	std::vector<HANDLE> mThreadHandle;
};

class IOCP : public ServerModel
{
public:
	IOCP();
	virtual ~IOCP();
public:
	void Initialize() override;
	void AddUser(const User* user) override;
	bool Run() override;
	void Release() override;
private:
	DWORD	   mNumofProcess;
	IOCPThread miocpThread;
	HANDLE	   mhComport;
};
