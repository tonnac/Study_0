#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <iostream>
#include <WS2tcpip.h>	// InetNtop(), inet_ntop()
#include <map>
#include "Protocol.h"

#pragma comment(lib, "ws2_32")

bool BeginWinSock();
bool EndWinSock();
int SendMsg(SOCKET sock, char* msg, WORD type)
{
	UPACKET sendmsg;
	ZeroMemory(&sendmsg, sizeof(sendmsg));
	sendmsg.ph.len = strlen(msg);
	sendmsg.ph.type = type;
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

DWORD WINAPI ClientThread(LPVOID arg)
{
	SOCKET sock = (SOCKET)arg;
	int iRecvByte = 0;
	char buffer[BUF_SIZE] = { 0, };
	while (1)
	{
		iRecvByte += recv(sock, &buffer[iRecvByte], sizeof(char) * PACKET_HEADER_SIZE - iRecvByte, 0);
		if (iRecvByte == 0) break;
		if (iRecvByte == PACKET_HEADER_SIZE)
		{
			UPACKET packet;
			ZeroMemory(&packet, sizeof(packet));
			memcpy(&packet.ph.len, buffer, sizeof(char) * PACKET_HEADER_SIZE);
			int rByte = 0;
			do
			{
				int iRecvByte2 = recv(sock, (char*)&packet.msg[rByte], sizeof(char) * packet.ph.len - rByte, 0);
				if (iRecvByte2 == 0)
				{
					break;
				}
				rByte += iRecvByte;
			} while (packet.ph.len > rByte);

			iRecvByte = 0;
			switch (packet.ph.type)
			{
			case PACKET_CHAT_MSG:
			{
				printf("패킷완성%s", packet.msg);
				SendMsg(sock, packet.msg, packet.ph.type);
			}break;
			}
		}
		Sleep(1);
	}
	closesocket(sock);
	return 1;
}

struct User
{
	SOCKET sock;
	SOCKADDR_IN Addr;
};

int main(void)
{
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
			printf("%s, %d\n", inet_ntop(AF_INET, &clientaddr.sin_addr, ip, sizeof(ip)), ntohs(clientaddr.sin_port));
			DWORD threadID;
			HANDLE hThread = CreateThread(0, 0, ClientThread, (LPVOID)&client, 0, &threadID);
		}
	}

	closesocket(Listensock);
	if (EndWinSock() == false)
	{
		return -1;
	}
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