#include "stdafx.h"
#include "Network.h"

bool Network::Set(const u_short port, const char* address)
{
	int iRet = 0;
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	m_Sock = socket(AF_INET, SOCK_STREAM, 0);

	if (address == NULL)
	{

	}
	else
	{

	}
//	bind(m_Sock,,);
	listen(m_Sock, SOMAXCONN);
	return true;
}

void Network::Release()
{
	WSACleanup();
}

Network::Network()
{

}
Network::~Network()
{

}