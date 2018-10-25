#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32")
#define BUF_SZ 1024

typedef struct PER_IO
{
	PER_IO()
	{
		wsaBuf.buf = buf;
		wsaBuf.len = BUF_SZ;
	}
	SOCKET sock;
	SOCKADDR_IN sockAdr;
	WSABUF wsaBuf;
	char buf[BUF_SZ];
} PER_IO_DATA, *LPPER_IO_DATA;

void CALLBACK ReadCompRoutine(DWORD, DWORD, LPWSAOVERLAPPED, DWORD);
void CALLBACK WriteCompRoutine(DWORD, DWORD, LPWSAOVERLAPPED, DWORD);

int main(void)
{
	const u_short port = 12346;
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET hServSock, hclntSock;
	SOCKADDR_IN servAdr, clntAdr;
	int clntAdrSz = sizeof(clntAdr);

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
		ZeroMemory(&servAdr, sizeof(servAdr));
		hclntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &clntAdrSz);
		char IPAddr[INET_ADDRSTRLEN];
		InetNtopA(AF_INET, &clntAdr.sin_addr, IPAddr, INET_ADDRSTRLEN);
		std::cout << "Client Connected IP : " << IPAddr << " Port : " << ntohs(clntAdr.sin_port) << std::endl;
		LPPER_IO_DATA ioinfo = new PER_IO;
		ioinfo->sock = hclntSock;
		CopyMemory(&ioinfo->sockAdr, &clntAdr, sizeof(clntAdr));
		LPOVERLAPPED lpoverlapped = new OVERLAPPED;
		ZeroMemory(lpoverlapped, sizeof(OVERLAPPED));
		lpoverlapped->hEvent = (HANDLE)ioinfo;
		DWORD RecvBytes, flaginfo = 0;
		WSARecv(ioinfo->sock, &ioinfo->wsaBuf, 1, &RecvBytes, &flaginfo, lpoverlapped, ReadCompRoutine);
	}

	closesocket(hServSock);
	WSACleanup();
	return 0;
}

void CALLBACK ReadCompRoutine(DWORD dwError, DWORD dwByte, LPWSAOVERLAPPED lpOverlapped, DWORD flags)
{
	LPPER_IO_DATA hbinfo = (LPPER_IO_DATA)lpOverlapped->hEvent;
	SOCKET hSock = hbinfo->sock;
	SOCKADDR_IN sockAdr = hbinfo->sockAdr;
	LPWSABUF bufInfo = &(hbinfo->wsaBuf);
	DWORD SentBytes = 0;

	if (dwByte == 0)
	{
		char IPAddr[INET_ADDRSTRLEN];
		InetNtopA(AF_INET, &sockAdr.sin_addr, IPAddr, INET_ADDRSTRLEN);
		std::cout << "Client Disconnected IP : " << IPAddr << ", Port : " << ntohs(sockAdr.sin_port) << std::endl;
		closesocket(hSock);
		delete hbinfo; delete lpOverlapped;
	}
	else
	{
		DWORD sendByes;
		bufInfo->len = dwByte;
		WSASend(hSock, bufInfo, 1, &sendByes, 0, lpOverlapped, WriteCompRoutine);
	}
}
void CALLBACK WriteCompRoutine(DWORD dwError, DWORD dwByte, LPWSAOVERLAPPED lpOverlapped, DWORD flags)
{
	HANDLE hbhandle = lpOverlapped->hEvent;
	LPPER_IO_DATA hbinfo = (LPPER_IO_DATA)lpOverlapped->hEvent;
	SOCKET hSock = hbinfo->sock;
	SOCKADDR_IN sockAdr = hbinfo->sockAdr;
	LPWSABUF bufInfo = &(hbinfo->wsaBuf);

	ZeroMemory(lpOverlapped, sizeof(OVERLAPPED));
	hbinfo->wsaBuf.buf = hbinfo->buf;
	hbinfo->wsaBuf.len = BUF_SZ;
	lpOverlapped->hEvent = hbhandle;

	DWORD recvByte, flaginfo = 0;
	WSARecv(hSock, &hbinfo->wsaBuf, 1, &recvByte, &flaginfo, lpOverlapped, ReadCompRoutine);
}