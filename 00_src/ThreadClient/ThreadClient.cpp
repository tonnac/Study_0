#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <process.h>
#include <conio.h>

#pragma comment(lib, "ws2_32")

#define BUF_SZ 512
UINT WINAPI ThreadFunc(LPVOID arg);
BOOL Quit;
char buf[BUF_SZ];

void CALLBACK CompRoutine(DWORD, DWORD, LPWSAOVERLAPPED, DWORD);

int main()
{
	Quit = FALSE;
	const u_short port = 12346;
	const char IPAddr[INET_ADDRSTRLEN] = "192.168.0.51";
	SOCKET hSock;
	SOCKADDR_IN sockAdr;
	WSADATA wsaData;

	WSAStartup(MAKEWORD(2, 2), &wsaData);
	ZeroMemory(&sockAdr, sizeof(sockAdr));

	hSock = socket(AF_INET, SOCK_STREAM, 0);

	sockAdr.sin_family = AF_INET;
	sockAdr.sin_port = htons(port);
	InetPtonA(AF_INET, IPAddr, &sockAdr.sin_addr);

	WSAOVERLAPPED wsaOverlapped;
	WSABUF wsaBuf;
	wsaBuf.buf = buf;
	wsaBuf.len = BUF_SZ;
	ZeroMemory(&wsaOverlapped, sizeof(WSAOVERLAPPED));
	wsaOverlapped.hEvent = &wsaBuf;
	connect(hSock, (SOCKADDR*)&sockAdr, sizeof(sockAdr));
	HANDLE ThreadHandle = (HANDLE)_beginthreadex(NULL, 0, ThreadFunc, (LPVOID)hSock, 0, NULL);
	DWORD dwRet;
	do
	{
		SleepEx(100, TRUE);
		DWORD recvBytes, flaginfo = 0;
		int retval;
		retval = WSARecv(hSock, &wsaBuf, 1, &recvBytes, &flaginfo, &wsaOverlapped, CompRoutine);
		if (retval == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSA_IO_PENDING)
			{
				continue;
			}
		}
	} while (Quit != TRUE);

	dwRet = WaitForSingleObject(ThreadHandle, INFINITE);
	if (dwRet == WAIT_FAILED)
	{
		std::cout << "Thread Error" << std::endl;
		return -1;
	}


	return 0;
}

UINT WINAPI ThreadFunc(LPVOID arg)
{
	SOCKET hSock = (SOCKET)arg;
	do
	{
		char buf[BUF_SZ];
		if (_kbhit())
		{
			fgets(buf, BUF_SZ, stdin);
			if (_stricmp(buf, "q\n") == 0)
			{
				Quit = TRUE;
				continue;
			}
			int SentByte = send(hSock, buf, strlen(buf) + 1, 0);
		}
	} while (Quit != TRUE);
	return 1;
}

void CALLBACK CompRoutine(DWORD dwError, DWORD dwByte, LPWSAOVERLAPPED lpOverlapped, DWORD flags)
{
	if (dwError != 0 || dwByte == 0)
	{
		std::cout << "Server Disconnect" << std::endl;
		Quit = TRUE;
		return;
	}
	HANDLE bufhandle = lpOverlapped->hEvent;
	WSABUF wsaBuf = *((LPWSABUF)lpOverlapped->hEvent);

	std::cout << "Received Message : " << wsaBuf.buf;

	ZeroMemory(lpOverlapped, sizeof(WSAOVERLAPPED));
	wsaBuf.buf = buf;
	wsaBuf.len = BUF_SZ;
	lpOverlapped->hEvent = bufhandle;
}