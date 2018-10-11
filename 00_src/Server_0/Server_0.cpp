#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <WinSock2.h>
#include <vector>


#pragma comment(lib,"ws2_32.lib")

std::vector<SOCKET> g_userList;

int main()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		return -1;
	}
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	//TCP
	//SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);	//UDP
	if (sock == INVALID_SOCKET)
	{
		return -1;
	}

	SOCKADDR_IN addr;
	ZeroMemory(&addr, sizeof(SOCKADDR_IN));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(10000);

	int ret = bind(sock, (sockaddr*)&addr, sizeof(addr));
	if (ret == SOCKET_ERROR)
	{
		return -1;
	}

	ret = listen(sock, SOMAXCONN);
	if (ret == SOCKET_ERROR)
	{
		return -1;
	}

	SOCKET clientSock;
	SOCKADDR_IN clientInfo;
	int addlen = sizeof(clientInfo);
	char buffer[256];
	while (1)
	{
		clientSock = accept(sock, (sockaddr*)&clientInfo, &addlen);
		if (clientSock == INVALID_SOCKET)
		{
			break;
		}
		std::cout << "\n" << inet_ntoa(clientInfo.sin_addr) << ", " << ntohs(clientInfo.sin_port);

		while (1)
		{
			send(clientSock, buffer, sizeof(buffer), 0);
			ret = recv(clientSock, buffer, sizeof(buffer), 0);
		}
	}
	closesocket(sock);
	WSACleanup();
	return 0;
}