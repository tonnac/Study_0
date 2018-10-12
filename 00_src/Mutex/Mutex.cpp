#include "Sample.h"

int main(void)
{
	//InitializeCriticalSection(&g_crit);
	g_hMutex = CreateMutex(nullptr, FALSE, L"KGCA");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(g_hMutex);
		return -1;
	}
	const u_short port = 10000;
	if (BeginWinSock() == false)
	{
		return -1;
	}

	SOCKET Listensock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	//	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_addr.s_addr = inet_addr("192.168.0.51");
//	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	int iRet = bind(Listensock, (sockaddr*)&addr, sizeof(addr));
	if (iRet != 0)
	{
		return -1;
	}

	iRet = listen(Listensock, SOMAXCONN);
	if (iRet != 0)
	{
		return -1;
	}

	char ip[INET_ADDRSTRLEN] = { 0, };

	while (1)
	{
		SOCKET client;
		SOCKADDR_IN clientaddr;
		int AddrLen = sizeof(clientaddr);
		client = accept(Listensock, (sockaddr*)&clientaddr, &AddrLen);
		if (client != SOCKET_ERROR)
		{
			AddUser({ client, clientaddr });
			printf("%s, %d\n", inet_ntop(AF_INET, &clientaddr.sin_addr, ip, sizeof(ip)), ntohs(clientaddr.sin_port));
			DWORD threadID;
			HANDLE hThread = CreateThread(0, 0, ClientThread, (LPVOID)client, 0, &threadID);
		}
	}

	closesocket(Listensock);
	if (EndWinSock() == false)
	{
		return -1;
	}
	CloseHandle(g_hMutex);
	return 0;
}