#pragma once
#include "Thread.h"

class Acceptor : public Thread
{
public:
	Acceptor();
	virtual ~Acceptor();
public:
	static UINT WINAPI AcceptThread(LPVOID arg);
	HANDLE CreateThreadandRun() override;
	bool setIPAndPort(u_short port, const TCHAR * IPAddr = nullptr);
	void Release();
private:
	bool Run() override;
private:
	WSAEVENT mAcceptEvent;
	SOCKET mlistenSock;
};