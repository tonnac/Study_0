#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <iostream>
#include <WS2tcpip.h>	// InetNtop(), inet_ntop()
#include <map>

#pragma comment(lib, "ws2_32")

bool BeginWinSock();
bool EndWinSock();

struct User
{
	SOCKET sock;
	SOCKADDR_IN Addr;
};


void zMSG(User * pUser, const char* msg)
{
	printf("%s, %s\n", inet_ntoa(pUser->Addr.sin_addr) ,msg);
}

int main(void)
{
	const u_short port = 10000;

	if (BeginWinSock() == false)
	{
		return -1;
	}

	// Create Socket
	// IP + Port -> bind -> 운영체제
	// Port를 사용하고 있는 프로세스(실행파일을 구분하는 용도)에게 알려준다.
	// listen ->  듣다.
	//
	
	SOCKET Listensock = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

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

	u_long on = TRUE;
	ioctlsocket(Listensock, FIONBIO, &on);

	char buffer[] = { "qqqq" };
	char ip[INET_ADDRSTRLEN] = { 0, };

	std::map<int ,User> g_userList;

	int g_iNumUser = 0;

	while (g_iNumUser != 1)
	{
		User user;
		int AddrLen = sizeof(user.Addr);
		user.sock = accept(Listensock, (sockaddr*)&user.Addr, &AddrLen);
		if (user.sock == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				exit(1);
			}
		}
		else
		{
			g_userList.insert(std::make_pair(g_iNumUser++, user));
			printf("%s, %d\n", inet_ntop(AF_INET, &user.Addr.sin_addr, ip, sizeof(ip)), ntohs(user.Addr.sin_port));
		}
	}
	while (1)
	{
		char recvmsg[256] = { 0, };
		int iRecvByte = sizeof(recvmsg);
		std::map<int, User>::iterator iter;
		for (iter = g_userList.begin(); iter != g_userList.end(); ++iter)
		{
			User * pUser = &iter->second;
			int iByte = recv(pUser->sock, recvmsg, iRecvByte, 0);
			if (iByte == 0)
			{
				iter = g_userList.erase(iter);
				closesocket(pUser->sock);
				break;
			}
			if (iByte == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK)
				{
					exit(1);
				}
			}
			else
			{
				send(pUser->sock, recvmsg, iByte, 0);
			}
		}
	}

	char msg[] = "RRRRR";
	int iSendByte = sizeof(msg);
	for (int iUser = 0; iUser < g_userList.size(); ++iUser)
	{
		send(g_userList[iUser].sock, msg, iSendByte, 0);
	}

	for (int iUser = 0; iUser < g_userList.size(); ++iUser)
	{
		closesocket(g_userList[iUser].sock);
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