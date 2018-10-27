#pragma once
#include "Acceptor.h"



class Server
{
public:
	Server();
	virtual ~Server();
public:
	bool isExit() const;
public:
	void AddUser(const SOCKET& clntSock, const SOCKADDR_IN clntAdr);
private:
	Acceptor mAcceptor;
	bool misExit = false;
};