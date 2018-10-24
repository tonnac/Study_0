#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32")
#define BUF_SZ 1024

typedef struct SOCK_INFO
{
	SOCK_INFO() : recvBytes(0), sendBytes(0)
	{
		wsabuf.buf = buf;
		wsabuf.len = BUF_SZ + 1;
		ZeroMemory(&Overlapped, sizeof(Overlapped));
	}
	OVERLAPPED Overlapped;
	SOCKET sock;
	SOCKADDR_IN sockAdr;
	char buf[BUF_SZ + 1];
	DWORD recvBytes;
	DWORD sendBytes;
	WSABUF wsabuf;
} *LPSOCK_INFO;

int nTotalSocket = 0;
LPSOCK_INFO SockArr[WSA_MAXIMUM_WAIT_EVENTS];
WSAEVENT EventArr[WSA_MAXIMUM_WAIT_EVENTS];
CRITICAL_SECTION cs;

DWORD WINAPI WorkerThread(LPVOID arg);

BOOL AddSocketInfo(const SOCKET& sock, const SOCKADDR_IN& sockAdr);
void RemoveSocketInfo(const int& nIndex);

int main(void)
{
	InitializeCriticalSection(&cs);
	const u_short port = 12346;
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET hServSock, hclntSock;
	SOCKADDR_IN servAdr, clntAdr;
	int clntAdrSz = sizeof(clntAdr);
	
	EventArr[nTotalSocket++] = WSACreateEvent();

	ZeroMemory(&servAdr, sizeof(servAdr));

	hServSock = socket(AF_INET, SOCK_STREAM, 0);

	servAdr.sin_family = AF_INET;
	servAdr.sin_port = htons(port);
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);

	int iRet;
	iRet = bind(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr));
	iRet = listen(hServSock, SOMAXCONN);

	while (1)
	{
		ZeroMemory(&clntAdr, sizeof(clntAdr));
		hclntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &clntAdrSz);
		if (AddSocketInfo(hclntSock, clntAdr) == TRUE)
		{
			char IPAddr[INET_ADDRSTRLEN];
			InetNtopA(AF_INET, &clntAdr.sin_addr, IPAddr, INET_ADDRSTRLEN);
			std::cout << "Client Connected IP : " << IPAddr << ", Port : " << ntohs(clntAdr.sin_port) << std::endl;
		}

		LPSOCK_INFO lpSockinfo = SockArr[nTotalSocket - 1];

		DWORD flaginfo = 0;
		WSARecv(lpSockinfo->sock, &lpSockinfo->wsabuf, 1, &lpSockinfo->recvBytes, &flaginfo, &lpSockinfo->Overlapped, NULL);

		WSASetEvent(EventArr[0]);
	}

	closesocket(hServSock);
	DeleteCriticalSection(&cs);
	WSACleanup();
	return 0;
}

DWORD WINAPI WorkerThread(LPVOID arg)
{
	int retval;
	while (1)
	{
		DWORD index = WSAWaitForMultipleEvents(nTotalSocket, EventArr, FALSE, WSA_INFINITE, FALSE);
		if (index == WSA_WAIT_FAILED) continue;
		index -= WSA_WAIT_EVENT_0;
		WSAResetEvent(EventArr[index]);
		if (index == 0) continue;

		LPSOCK_INFO lpSockinfo = SockArr[index];
		SOCKADDR_IN clntAdr = lpSockinfo->sockAdr;
		DWORD cbTrans;
		retval = GetOverlappedResult((HANDLE)lpSockinfo->sock, &lpSockinfo->Overlapped, &cbTrans, FALSE);

		char IPAddr[INET_ADDRSTRLEN];
		InetNtopA(AF_INET, &clntAdr.sin_addr, IPAddr, INET_ADDRSTRLEN);

		if (retval == FALSE || cbTrans == 0)
		{
			RemoveSocketInfo(index);
			std::cout << "Disconnected IP : " << IPAddr << "Port : " << ntohs(clntAdr.sin_port) << std::endl;
			continue;
		}

		if (lpSockinfo->recvBytes == 0)
		{
			lpSockinfo->recvBytes = cbTrans;

		}

	}


	return 1;
}

BOOL AddSocketInfo(const SOCKET& sock, const SOCKADDR_IN& sockAdr)
{
	EnterCriticalSection(&cs);

	if (nTotalSocket >= WSA_MAXIMUM_WAIT_EVENTS) return FALSE;
	LPSOCK_INFO lpSock = new SOCK_INFO;
	lpSock->sock = sock;
	CopyMemory(&lpSock->sockAdr, &sockAdr, sizeof(SOCKADDR_IN));
	lpSock->Overlapped.hEvent = WSACreateEvent();
	SockArr[nTotalSocket] = lpSock;
	EventArr[nTotalSocket++] = lpSock->Overlapped.hEvent;

	LeaveCriticalSection(&cs);
	return TRUE;
}
void RemoveSocketInfo(const int& nIndex)
{
	EnterCriticalSection(&cs);

	closesocket(SockArr[nIndex]->sock);
	WSACloseEvent(EventArr[nIndex]);
	delete SockArr[nIndex];

	if (nIndex != (nTotalSocket - 1))
	{
		SockArr[nIndex] = SockArr[nTotalSocket - 1];
		EventArr[nIndex] = EventArr[nTotalSocket - 1];
	}
	--nTotalSocket;

	LeaveCriticalSection(&cs);
}