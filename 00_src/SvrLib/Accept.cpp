#include "stdafx.h"
#include "Accept.h"
#include "SvrIOCP.h"

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
		if (clientSocket == INVALID_SOCKET)
		{
			continue;
		}
		char buf[INET_ADDRSTRLEN];
		InetNtopA(AF_INET, &clientAddr.sin_addr, buf, sizeof(buf));
		AddUser(clientSocket, clientAddr);
		
		Sleep(1);
	}
}

User* Accept::AddUser(SOCKET clientSock, SOCKADDR_IN clientAddr)
{
	User * pUser = I_User.AddUser(clientSock, clientAddr);
	if (pUser != NULL)
	{
		I_IOCP.Add((HANDLE)pUser->m_Sock, (ULONG_PTR)pUser);
		pUser->RecvData();
	}
	return pUser;
}

Accept::Accept()
{

}
Accept::~Accept()
{

}