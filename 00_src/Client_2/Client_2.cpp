#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <WinSock2.h>
#include "Protocol.h"

#pragma comment(lib,"ws2_32.lib")
int SendMsg(SOCKET sock, char* msg, WORD type)
{
	UPACKET sendmsg;
	ZeroMemory(&sendmsg, sizeof(sendmsg));
	sendmsg.ph.len = strlen(msg);
	sendmsg.ph.type = type;
	memcpy(&sendmsg.msg, msg, sendmsg.ph.len);
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
	addr.sin_addr.s_addr = inet_addr("192.168.0.101");
	addr.sin_port = htons(port);

	int ret;
	ret = connect(sock, (sockaddr*)&addr, sizeof(addr));
	if (ret == SOCKET_ERROR)
	{
		return -1;
	}

	DWORD threadID;
	HANDLE hThread = CreateThread(NULL, 0, SendThread, (LPVOID)sock, 0, &threadID);
	CloseHandle((HANDLE)hThread);
	while (true)
	{
		char buffer[BUF_SIZE] = { 0, };
		int iRecvByte = 0;
		while (true)
		{
			iRecvByte += recv(sock, &buffer[iRecvByte], sizeof(char) * PACKET_HEADER_SIZE - iRecvByte, 0);
			if (iRecvByte == PACKET_HEADER_SIZE)
			{
				UPACKET packet;
				ZeroMemory(&packet, sizeof(packet));
				memcpy(&packet.ph.len, buffer, sizeof(char) * PACKET_HEADER_SIZE);
				int rByte = 0;
				do
				{
					rByte += recv(sock, (char*)&packet.msg[rByte], sizeof(char) * packet.ph.len - rByte, 0);
				} while (packet.ph.len > rByte);

				iRecvByte = 0;
				switch (packet.ph.type)
				{
				case PACKET_CHAT_MSG:
				{
					printf("패킷완성%s", packet.msg);
				}break;
				default:
					break;
				}
			}
		}
	}
	closesocket(sock);
	WSACleanup();
	return 0;
}