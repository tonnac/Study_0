#include "Network.h"

bool Network::Set(const u_short port, const char* address)
{
	int iRet = 0;
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (m_Sock = socket(AF_INET, SOCK_STREAM, 0) == INVALID_SOCKET)
	{
		return false;
	}

	SOCKADDR_IN servAdr;
	ZeroMemory(&servAdr, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_port = htons(port);

	if (address == NULL)
	{
		servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	else
	{
		InetPtonA(AF_INET, address, &servAdr.sin_addr);
	}
	ExptSocketError(bind(m_Sock, (SOCKADDR*)&servAdr, sizeof(servAdr)));
	ExptSocketError(listen(m_Sock, SOMAXCONN));
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