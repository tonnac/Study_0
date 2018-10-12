#pragma once
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
	User() {}
	User(SOCKET client, SOCKADDR_IN add) : sock(client), Addr(add)
	{}
	User(const User& user) : sock(user.sock), Addr(user.Addr)
	{}
};

std::map<SOCKET, User> g_allUser;
using User_Iter = std::map<SOCKET, User>::iterator;
CRITICAL_SECTION	g_crit;
HANDLE				g_hMutex;

bool BeginWinSock();
bool EndWinSock();
int CheckReturn(const int& iRet);
void ErrorMsg();
void AddUser(User user);
int SendMsg(SOCKET sock, char* msg, WORD type);
int SendMsg(SOCKET sock, PACKET_HEADER ph, char* msg);
int SendMsg(SOCKET sock, UPACKET* uPacket);
int BroadCasting(char * pMsg);
void DelUser(User* pUser);
DWORD WINAPI ClientThread(LPVOID arg);

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
int CheckReturn(const int& iRet)
{
	if (iRet == 0)
	{
		return 0;
	}
	else if (iRet <= SOCKET_ERROR)
	{
		ErrorMsg();
		return -1;
	}
	return iRet;
}
void ErrorMsg()
{
	char* pMsg = nullptr;
	FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&pMsg, 0, NULL);
	printf("\n%s", pMsg);
	LocalFree(pMsg);
}
void AddUser(User user)
{
	//	EnterCriticalSection(&g_crit);
	DWORD dwRet = WaitForSingleObject(g_hMutex, INFINITE);
	if (dwRet != WAIT_TIMEOUT)
	{
		g_allUser.insert(std::make_pair(user.sock, user));
	}
	ReleaseMutex(g_hMutex);
	//	LeaveCriticalSection(&g_crit);
}
DWORD WINAPI ClientThread(LPVOID arg)
{
	SOCKET sock = (SOCKET)arg;
	User* pUser = &g_allUser[sock];
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
		if (CheckReturn(iSend) <= 0)
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
	int iSend = 0;
	char* pMsg = (char*)&sendmsg;
	do
	{
		iSend = send(sock, &pMsg[iSendByte], iTotalSize - iSendByte, 0);
		if (CheckReturn(iSend) <= 0)
		{
			return iSend;
		}
		iSendByte += iSend;
	} while (iTotalSize > iSendByte);
	return sendmsg.ph.len + PACKET_HEADER_SIZE;
}
int SendMsg(SOCKET sock, UPACKET* uPacket)
{
	int iSendByte = 0;
	int iTotalSize = strlen(uPacket->msg) + PACKET_HEADER_SIZE;
	char* pMsg = (char*)&uPacket;
	int iSend = 0;
	do
	{
		iSend = send(sock, &pMsg[iSendByte], iTotalSize - iSendByte, 0);
		if (CheckReturn(iSend) <= 0)
		{
			return iSend;
		}
		iSendByte += iSend;
	} while (iTotalSize > iSendByte);
	return uPacket->ph.len + PACKET_HEADER_SIZE;
}
void DelUser(User* pUser)
{
	printf("\nip:%s, port=%d 나감\n", inet_ntoa(pUser->Addr.sin_addr), ntohs(pUser->Addr.sin_port));
	//	EnterCriticalSection(&g_crit);
	DWORD dwRet = WaitForSingleObject(g_hMutex, INFINITE);
	{
		User_Iter iter = g_allUser.find(pUser->sock);
		if (iter != g_allUser.end())
		{
			g_allUser.erase(iter);
		}
	}
	ReleaseMutex(g_hMutex);
	//	LeaveCriticalSection(&g_crit);
}
int BroadCasting(char * pMsg)
{
	//	EnterCriticalSection(&g_crit);
	DWORD dwRet = WaitForSingleObject(g_hMutex, INFINITE);
	for (User_Iter iter = g_allUser.begin(); iter != g_allUser.end();)
	{
		User * pUser = &iter->second;
		if (pUser != nullptr)
		{
			if (SendMsg(pUser->sock, pMsg, PACKET_CHAT_MSG) <= 0)
			{
				closesocket(pUser->sock);
				g_allUser.erase(iter++);
			}
			else
			{
				++iter;
			}
		}
	}
	ReleaseMutex(g_hMutex);
	//	LeaveCriticalSection(&g_crit);
	return -1;
}