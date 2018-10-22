#pragma once
#include "Thread.h"
#include "Network.h"
#include "User.h"

class Accept : public Thread
{
	Network m_network;
public:
	bool Set(const u_short port, const char* address = NULL);
	void Run() override;
	virtual bool AddUser(SOCKET clientSock, SOCKADDR_IN clientAddr);
public:
	Accept();
	virtual ~Accept();
};