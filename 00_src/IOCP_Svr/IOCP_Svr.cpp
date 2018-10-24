#include <iostream>
#include <process.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32")
#define BUF_SZ 1024

enum class IOState
{
	RECV,
	SEND
};

typedef struct HANDLE_DATA
{
	HANDLE_DATA(const SOCKET& _sock, const SOCKADDR_IN& _sockAdr) : sock(_sock), sockAdr(_sockAdr)
	{}
	SOCKET sock;
	SOCKADDR_IN sockAdr;
} PER_HANDLE_DATA, *LPPER_HANDLE_DATA;

typedef struct PER_IO
{
	PER_IO()
	{
		wsaBuf.buf = buf;
		wsaBuf.len = BUF_SZ;
		iostate = IOState::RECV;
		ZeroMemory(&overlapped, sizeof(OVERLAPPED));
	}
	OVERLAPPED overlapped;
	IOState iostate;
	WSABUF wsaBuf;
	char buf[BUF_SZ];
} PER_IO_DATA, *LPPER_IO_DATA;

UINT WINAPI EchoThread(LPVOID arg);

int main(void)
{
	const u_short port = 12346;
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET hServSock, hclntSock;
	SOCKADDR_IN servAdr, clntAdr;
	int clntAdrSz = sizeof(clntAdr);
	DWORD RecvBytes, flaginfo = 0;
	HANDLE hComport = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);

	{
		SYSTEM_INFO sysinfo;
		GetSystemInfo(&sysinfo);
		for (int k = 0; k < sysinfo.dwNumberOfProcessors; ++k)
		{
			_beginthreadex(NULL, 0, EchoThread, (LPVOID)hComport, 0, NULL);
		}
	}

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
		LPPER_HANDLE_DATA hbinfo = new PER_HANDLE_DATA(hclntSock, clntAdr);
		LPPER_IO_DATA ioinfo = new PER_IO_DATA;
		CreateIoCompletionPort((HANDLE)hclntSock, hComport, (ULONG_PTR)hbinfo, 0);
		WSARecv(hbinfo->sock, &ioinfo->wsaBuf, 1, &RecvBytes, &flaginfo, &ioinfo->overlapped, NULL);
	}

	closesocket(hServSock);
	WSACleanup();
	return 0;
}


UINT WINAPI EchoThread(LPVOID arg)
{
	HANDLE hComport = (HANDLE)arg;
	DWORD Bytes;
	LPPER_IO_DATA ioinfo;
	LPPER_HANDLE_DATA hbinfo;
	while (1)
	{
		GetQueuedCompletionStatus(hComport, &Bytes, (PULONG_PTR)&hbinfo, (LPOVERLAPPED*)&ioinfo, INFINITE);

		switch (ioinfo->iostate)
		{
			case IOState::RECV:
			{
				if (Bytes == SOCKET_ERROR || Bytes == 0)
				{
					char IPAddr[INET_ADDRSTRLEN];
					InetNtopA(AF_INET, &hbinfo->sockAdr, IPAddr, INET_ADDRSTRLEN);
					std::cout << "Client Disconnected IP : " << IPAddr << ", Port : " << ntohs(hbinfo->sockAdr.sin_port) << std::endl;
					closesocket(hbinfo->sock);
					delete ioinfo; delete hbinfo;
				}
				else
				{
					ioinfo->iostate = IOState::SEND;
					ioinfo->wsaBuf.len = Bytes;
					WSASend(hbinfo->sock, &ioinfo->wsaBuf, 1, &Bytes, 0, &ioinfo->overlapped, NULL);
				}
			}break;
				case IOState::SEND:
				{
					DWORD flaginfo = 0;
					std::cout << "Message Send!" << std::endl;
					delete ioinfo;
					LPPER_IO_DATA nioinfo = new PER_IO;
					WSARecv(hbinfo->sock, &nioinfo->wsaBuf, 1, &Bytes, &flaginfo, &nioinfo->overlapped, NULL);

				}break;
			default:
				break;
		}

	}
}