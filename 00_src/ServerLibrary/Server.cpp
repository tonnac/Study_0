#include "Server.h"

Server::Server() : mAcceptor(this)
{

}

Server::~Server()
{}

bool Server::isExit() const
{
	return misExit;
}

void Server::AddUser(const SOCKET& clntSock, const SOCKADDR_IN clntAdr)
{

}