#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <iostream>
#include <WS2tcpip.h>	// InetNtop(), inet_ntop()
#include <map>
#include "Protocol.h"

#pragma comment(lib, "ws2_32")

struct User
{
	SOCKET			sock;
	SOCKADDR_IN		Addr;
	int				iIndex;
};

User	g_allUser[100];
int		g_iNumClient = 0;

CRITICAL_SECTION g_crit;

bool BeginWinSock();
bool EndWinSock();
void AddUser(User user);
int SendMsg(SOCKET sock, char* msg, WORD type);
int SendMsg(SOCKET sock, PACKET_HEADER ph, char* msg);
int SendMsg(SOCKET sock, UPACKET* uPacket);
int BroadCasting(char * pMsg);
void DelUser(User* pUser);
DWORD WINAPI ClientThread(LPVOID arg);

int main(void)
{
	InitializeCriticalSection(&g_crit);
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
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

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
			User user;
			user.sock = client;
			user.Addr = clientaddr;
			AddUser(user);
			printf("%s, %d\n", inet_ntop(AF_INET, &clientaddr.sin_addr, ip, sizeof(ip)), ntohs(clientaddr.sin_port));
			DWORD threadID;
			HANDLE hThread = CreateThread(0, 0, ClientThread, (LPVOID)&g_allUser[g_iNumClient - 1], 0, &threadID);
		}
	}

	closesocket(Listensock);
	if (EndWinSock() == false)
	{
		return -1;
	}
	DeleteCriticalSection(&g_crit);
	return 0;
}


bool BeginWinSock()
{
	WSADATA wsaData;
	int iRet = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iRet != 0) return false;
	return true;
}
bool EndWinSock()
{
	int iRet = WSACleanup();
	if (iRet != 0) return false;
	return true;
}
void AddUser(User user)
{
	EnterCriticalSection(&g_crit);
	g_allUser[g_iNumClient] = user;
	++g_iNumClient;
	LeaveCriticalSection(&g_crit);
}
DWORD WINAPI ClientThread(LPVOID arg)
{
	User* pUser = (User*)arg;
	SOCKET sock = pUser->sock;
	int iRecvByte = 0;
	int iRet = 0;
	char buffer[BUF_SIZE] = { 0, };
	bool bConnect = true;
	while (bConnect == true)
	{
		iRet = recv(sock, &buffer[iRecvByte], sizeof(char) * PACKET_HEADER_SIZE - iRecvByte, 0);
		if (iRet == 0 || iRet == SOCKET_ERROR)
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
				if (iRecvByte2 == 0 || iRecvByte2 == SOCKET_ERROR)
				{
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
	DelUser(pUser);
	return 1;
}
int SendMsg(SOCKET sock, char* msg, WORD type)
{
	UPACKET sendmsg;
	ZeroMemory(&sendmsg, sizeof(sendmsg));
	sendmsg.ph.len = strlen(msg);
	sendmsg.ph.type = type;
	memcpy(&sendmsg.msg, msg, strlen(msg));
	int iSendByte = 0;
	int iTotalSize = sendmsg.ph.len + PACKET_HEADER_SIZE;
	int iSend = 0;
	char* pMsg = (char*)&sendmsg;
	do
	{
		iSend = send(sock, &pMsg[iSendByte], iTotalSize - iSendByte, 0);
		if (iSend == SOCKET_ERROR)
		{
			return iSend;
		}
		iSendByte += iSend;
	} while (iTotalSize > iSendByte);
	return sendmsg.ph.len + PACKET_HEADER_SIZE;
}
int SendMsg(SOCKET sock, PACKET_HEADER ph, char* msg)
{
	UPACKET sendmsg;
	ZeroMemory(&sendmsg, sizeof(sendmsg));
	sendmsg.ph = ph;
	memcpy(&sendmsg.msg, msg, sizeof(msg));
	int iSendByte = 0;
	int iTotalSize = sendmsg.ph.len + PACKET_HEADER_SIZE;
	char* pMsg = (char*)&sendmsg;
	do
	{
		iSendByte += send(sock, &pMsg[iSendByte], iTotalSize - iSendByte, 0);
	} while (iTotalSize > iSendByte);
	return sendmsg.ph.len + PACKET_HEADER_SIZE;
}
int SendMsg(SOCKET sock, UPACKET* uPacket)
{
	int iSendByte = 0;
	int iTotalSize = strlen(uPacket->msg) + PACKET_HEADER_SIZE;
	char* pMsg = (char*)&uPacket;
	do
	{
		iSendByte += send(sock, &pMsg[iSendByte], iTotalSize - iSendByte, 0);
	} while (iTotalSize > iSendByte);
	return uPacket->ph.len + PACKET_HEADER_SIZE;
}
void DelUser(User* pUser)
{
	printf("\nip:%s, port=%d 나감\n", inet_ntoa(pUser->Addr.sin_addr), ntohs(pUser->Addr.sin_port));
	EnterCriticalSection(&g_crit);
	{
		for (int iUser = 0; iUser < g_iNumClient; ++iUser)
		{
			if (g_allUser[iUser].sock == pUser->sock)
			{
				for (int iDel = iUser; iDel < g_iNumClient - 1; ++iDel)
				{
					g_allUser[iDel] = g_allUser[iDel + 1];
				}
				--g_iNumClient;
				break;
			}
		}
		closesocket(pUser->sock);
	}
	LeaveCriticalSection(&g_crit);
}
int BroadCasting(char * pMsg)
{
	EnterCriticalSection(&g_crit);
	for (int iUser = 0; iUser < g_iNumClient; ++iUser)
	{
		if (SendMsg(g_allUser[iUser].sock, pMsg, PACKET_CHAT_MSG) <= 0)
		{
			continue;
		}
	}
	LeaveCriticalSection(&g_crit);
	return -1;
}