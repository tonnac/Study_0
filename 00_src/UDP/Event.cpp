#include "Sample.h"

HANDLE g_hEvent = nullptr;

#define Zerom(x) memset(&(x), 0, (sizeof(x)))

DWORD WINAPI SendThread(LPVOID Param)
{
	SOCKET sock = (SOCKET)Param;
	while (1)
	{
		char buffer[256] = { 0, };
		fgets(buffer, 256, stdin);
		if (strlen(buffer)-1 == 0)
		{
			break;
		}
		SendMsg(sock, buffer, PACKET_CHAT_MSG);
	}
	closesocket(sock);
	return 1;
}

DWORD WINAPI ConnectThread(LPVOID Param)
{
	const u_short port = 9000;
	const char* IPAddr = "127.0.0.1";

	SOCKET sock = (SOCKET)Param;
	SOCKADDR_IN addr;
	ZeroMemory(&addr, sizeof(SOCKADDR_IN));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(IPAddr);
//	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);

	int ret;
	ret = connect(sock, (sockaddr*)&addr, sizeof(addr));
	if (ret == SOCKET_ERROR)
	{
		return -1;
	}
	Sleep(3000);
	SetEvent(g_hEvent); // 신호상태로 전환
	while (1)
	{
		Sleep(1000);
	}
	return 1;
}
DWORD WINAPI RecvThread(LPVOID Param)
{
	SOCKET sock = (SOCKET)Param;
	int iRecvByte = 0;
	int iRet = 0;
	char buffer[BUF_SIZE] = { 0, };
	bool bConnect = true;
	while (bConnect == true)
	{
		iRet = recv(sock, &buffer[iRecvByte], sizeof(char) * PACKET_HEADER_SIZE - iRecvByte, 0);
		if (CheckReturn(iRet) <= 0)
		{
			break;
		}
		iRecvByte += iRet;
		if (iRecvByte == PACKET_HEADER_SIZE)
		{
			UPACKET packet;
			ZeroMemory(&packet, sizeof(packet));
			memcpy(&packet.ph.len, buffer, sizeof(char) * PACKET_HEADER_SIZE);
			int rByte = 0;
			do
			{
				int iRecvByte2 = recv(sock, (char*)&packet.msg[rByte], sizeof(char) * packet.ph.len - rByte, 0);
				if (CheckReturn(iRecvByte2) <= 0)
				{
					ErrorMsg();
					bConnect = false;
					break;
				}
				rByte += iRecvByte2;
			} while (packet.ph.len > rByte);

			iRecvByte = 0;

			if (bConnect == true)
			{
				switch (packet.ph.type)
				{
				case PACKET_CHAT_MSG:
				{
					BroadCasting(packet.msg);
					printf("패킷완성%s", packet.msg);
				}break;
				}
			}
		}
		Sleep(1);
	}
	closesocket(sock);
	return 1;
}
int main(void)
{
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	Zerom(addr);
//	const u_short port = atoi(argv[1]);
//	const char* IPAddr = argv[2];
	if (BeginWinSock() == false)
	{
		return -1;
	}

	g_hEvent = CreateEvent(NULL, 
		FALSE, // FALSE == 자동 리셋이벤트,			TRUE == 수동 리셋이벤트
		FALSE, // FALSE == Non_Signal(비신호상태),	TRUE == Signal(신호상태)
		L"ConnectEvent");

	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	//TCP
	if (sock == INVALID_SOCKET)
	{
		return -1;
	}
//	DWORD threadID_1;
//	HANDLE hConnectThread = CreateThread(NULL, 0, ConnectThread, (LPVOID)sock, 0, &threadID_1);
	
	//Event
//	WaitForSingleObject(g_hEvent, INFINITE);
	ResetEvent(g_hEvent);

	DWORD threadID_2;
	HANDLE hSendThread = CreateThread(NULL, 0, SendThread, (LPVOID)sock, 0, &threadID_2);

	DWORD threadID_3;
	HANDLE hRecvThread = CreateThread(NULL, 0, RecvThread, (LPVOID)sock, 0, &threadID_3);

//	WaitForSingleObject(hConnectThread, INFINITE);
	WaitForSingleObject(hSendThread, INFINITE);
	WaitForSingleObject(hRecvThread, INFINITE);

	closesocket(sock);

//	CloseHandle(hConnectThread);
	CloseHandle(hSendThread);
	CloseHandle(hRecvThread);
	if (EndWinSock() == false)
	{
		return -1;
	}
	return 0;
}