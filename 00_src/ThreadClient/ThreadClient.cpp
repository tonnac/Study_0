#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <process.h>
#include <conio.h>

#pragma comment(lib, "ws2_32")

#define BUF_SZ 512
UINT WINAPI ThreadFunc(LPVOID arg);
HANDLE g_Event;

int main()
{
	g_Event = CreateEvent(NULL, TRUE, FALSE, NULL);
	const u_short port = 12346;
	const char IPAddr[INET_ADDRSTRLEN] = "219.254.48.7";
	SOCKET hSock;
	SOCKADDR_IN sockAdr;
	WSADATA wsaData;

	WSAStartup(MAKEWORD(2, 2), &wsaData);
	ZeroMemory(&sockAdr, sizeof(sockAdr));

	hSock = socket(AF_INET, SOCK_STREAM, 0);

	sockAdr.sin_family = AF_INET;
	sockAdr.sin_port = htons(port);
	InetPtonA(AF_INET, IPAddr, &sockAdr.sin_addr);

	connect(hSock, (SOCKADDR*)&sockAdr, sizeof(sockAdr));
	HANDLE ThreadHandle = (HANDLE)_beginthreadex(NULL, 0, ThreadFunc, (LPVOID)hSock, 0, NULL);
	DWORD dwRet;
	do
	{
		int RecvByte;
		char buf[BUF_SZ];
		RecvByte = recv(hSock, buf, BUF_SZ, 0);
		if (RecvByte == SOCKET_ERROR)
		{
			SetEvent(g_Event);
			std::cout << "Disconnected Server" << std::endl;
			break;
		}
		std::cout << "Receive Message : " << buf;
		dwRet = WaitForSingleObject(ThreadHandle, NULL);
	} while (dwRet != WAIT_OBJECT_0);



	return 0;
}

UINT WINAPI ThreadFunc(LPVOID arg)
{
	SOCKET hSock = (SOCKET)arg;
	DWORD dwRet;
	do
	{
		char buf[BUF_SZ];
		fgets(buf, BUF_SZ, stdin);
		if (_stricmp(buf, "q\n") == 0)
		{
			break;
		}
		int SentByte = send(hSock, buf, strlen(buf) + 1, 0);
		dwRet = WaitForSingleObject(g_Event, NULL);
	} while (dwRet != WAIT_OBJECT_0);
	return 1;
}