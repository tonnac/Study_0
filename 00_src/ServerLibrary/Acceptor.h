#pragma once
#include "Thread.h"

class Server;

class Acceptor : public Thread
{
public:
	Acceptor(Server * server);
	virtual ~Acceptor();
public:
	bool setIPAndPort(u_short port, const TCHAR * IPAddr = nullptr);
	bool Run() override;
private:
	WSAEVENT mAcceptEvent;
	SOCKET mlistenSock;
	Server* mServer;
};