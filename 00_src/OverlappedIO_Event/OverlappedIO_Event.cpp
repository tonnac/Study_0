#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32")
#define BUF_SZ 1024

SOCKET hSockArr[WSA_MAXIMUM_WAIT_EVENTS];
WSAEVENT hEventArr[WSA_MAXIMUM_WAIT_EVENTS];

void DelSock(const int& idx, const int& socknum);

int main(void)
{
	const u_short port = 12346;
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET hServSock, hclntSock;
	SOCKADDR_IN servAdr, clntAdr;
	char buf[BUF_SZ];
	int clntAdrSz = sizeof(clntAdr);
	int numofSock = 0;
	int i;
	WSAEVENT wEvent;

	ZeroMemory(&servAdr, sizeof(servAdr));

	hServSock = socket(AF_INET, SOCK_STREAM, 0);

	servAdr.sin_family = AF_INET;
	servAdr.sin_port = htons(port);
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);

	int iRet;
	iRet = bind(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr));
	iRet = listen(hServSock, SOMAXCONN);

	wEvent = WSACreateEvent();
	hEventArr[numofSock] = wEvent;
	hSockArr[numofSock] = hServSock;
	WSAEventSelect(hServSock, wEvent, FD_ACCEPT);
	++numofSock;

	while (1)
	{

	}

	closesocket(hServSock);
	WSACleanup();
	return 0;
}

void DelSock(const int& idx, const int& socknum)
{
	for (int i = idx; i < socknum; ++i)
	{
		hSockArr[i] = hSockArr[i + 1];
		hEventArr[i] = hEventArr[i + 1];
	}
}