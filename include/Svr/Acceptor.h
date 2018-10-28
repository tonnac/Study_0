#pragma once
#include "Thread.h"

class Server;

class Acceptor : public Thread
{
public:
	Acceptor(Server * server);
	virtual ~Acceptor();
public:
	HANDLE CreateThreadandRun() override;
	bool setIPAndPort(u_short port, const TCHAR * IPAddr = nullptr);
	void Release();
private:
	bool Run() override;
private:
	WSAEVENT mAcceptEvent;
	SOCKET mlistenSock;
	Server* mServer;
};