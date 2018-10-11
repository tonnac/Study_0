#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <WinSock2.h>

#pragma comment(lib,"ws2_32.lib")

int main(int argc, char* argv[])
{
	const u_short port = atoi(argv[1]);
	const char* IPAddr = argv[2];

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

	int ret;
	ret = connect(sock, (sockaddr*)&addr, sizeof(addr));
	if (ret == SOCKET_ERROR)
	{
		return -1;
	}
	
	char buffer3[] = "Ready";
	int iRet;
	//do
	//{
	//	iRet = send(sock, buffer3, sizeof(buffer3), 0);
	//} while(iRet == 0 || iRet == SOCKET_ERROR);

//	iRet = send(sock, buffer3, sizeof(buffer3), 0);

	char buffer2[256];

	while (1)
	{
		char buffer[256] = { 0, };
		std::cin >> buffer;
		if (buffer[0] == '0')
		{
			break;
		}
		send(sock, buffer, strlen(buffer) + 1, 0);
		iRet = recv(sock, buffer2, sizeof(buffer2), 0);
		printf("%s\n", buffer2);
		ZeroMemory(buffer2, sizeof(buffer2));
		if (iRet == 0 || iRet == SOCKET_ERROR)
		{
			break;
		}
	}
	closesocket(sock);
	WSACleanup();
	return 0;
}