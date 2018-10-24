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
		int idx = WSAWaitForMultipleEvents(numofSock, hEventArr, FALSE, WSA_INFINITE, FALSE);
		int startidx = idx - WSA_WAIT_EVENT_0;

		for (i = startidx; i < numofSock; ++i)
		{
			int sigeventIdx = WSAWaitForMultipleEvents(1, &hEventArr[i], FALSE, NULL, FALSE);
			if (sigeventIdx == WSA_WAIT_TIMEOUT || sigeventIdx == WSA_WAIT_FAILED)
			{
				continue;
			}
			else
			{
				sigeventIdx = i;
				WSANETWORKEVENTS netevent;
				WSAEnumNetworkEvents(hSockArr[sigeventIdx], hEventArr[sigeventIdx], &netevent);
				if (netevent.lNetworkEvents & FD_ACCEPT)
				{
					if (netevent.iErrorCode[FD_ACCEPT_BIT] != 0)
					{
						std::cout << "Accept Error" << std::endl;
						exit(-1);
					}
					hclntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &clntAdrSz);
					if (hclntSock == INVALID_SOCKET)
					{
						std::cout << "accept Error" << std::endl;
						break;
					}
					wEvent = WSACreateEvent();
					char IPAddr[INET_ADDRSTRLEN];
					InetNtopA(AF_INET, &clntAdr.sin_addr, IPAddr, INET_ADDRSTRLEN);
					std::cout << "Client Connected IP : " << IPAddr << " Port : " << ntohs(clntAdr.sin_port) << std::endl;
					hEventArr[numofSock] = wEvent;
					hSockArr[numofSock] = hclntSock;
					WSAEventSelect(hclntSock, wEvent, FD_READ | FD_CLOSE);
					++numofSock;
				}
				if (netevent.lNetworkEvents & FD_READ)
				{
					if (netevent.iErrorCode[FD_READ_BIT] != 0)
					{
						std::cout << "Read Error" << std::endl;
						exit(-1);
					}
					int RecvByte = recv(hSockArr[sigeventIdx], buf, BUF_SZ, 0);
					send(hSockArr[sigeventIdx], buf, RecvByte, 0);
				}
				if (netevent.lNetworkEvents & FD_CLOSE)
				{
					if (netevent.iErrorCode[FD_CLOSE_BIT] != 0)
					{
						std::cout << "Close Error" << std::endl;
					}
					WSACloseEvent(hEventArr[numofSock]);
					closesocket(hSockArr[numofSock]);

					--numofSock;
					DelSock(sigeventIdx, numofSock);
				}
			}
		}
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