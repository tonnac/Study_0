#include "stdafx.h"
#include "Accept.h"

bool Accept::Set(const u_short port, const char* address)
{
	m_network.Set(port, address);
	return true;
}

void Accept::Run()
{
	SOCKET clientSocket;
	SOCKADDR_IN clientAddr;
	int addrlen;
	addrlen = sizeof(clientAddr);
	while (1)
	{
		clientSocket = accept(m_network.m_Sock, (SOCKADDR*)&clientAddr, &addrlen);

	}
}


Accept::Accept()
{

}
Accept::~Accept()
{

}