#include "header.h"

bool BeginWinSock();
bool EndWinSock();
DWORD WINAPI WorkerThread(LPVOID arg);
#define MAX_WORK_THREAD 4
#define BUF_SIZE 2048

#define RECV 1000
#define SEND 2000 

typedef struct OVERLAPPED_EX : OVERLAPPED
{
	DWORD flag;
} OVERLAPPED_EX, *LPOVERLAPPED_EX;

struct User
{
	User()
	{
		ZeroMemory(&ov, sizeof(ov));
		buffer.buf = buf;
		buffer.len = BUF_SIZE;
	}
	SOCKET sock;
	OVERLAPPED_EX ov;
	char buf[BUF_SIZE];
	WSABUF buffer;
};

User user;

HANDLE m_hIOCP;
HANDLE m_hWorkThread[MAX_WORK_THREAD];

int main()
{
	const u_short port = 10000;
	const char IPAddr[] = "127.0.0.1";
	BeginWinSock();


	SOCKET Listensock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	InetPtonA(AF_INET, IPAddr, &addr.sin_addr);

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


	DWORD id;
	for (int i = 0; i < MAX_WORK_THREAD; ++i)
	{
		m_hWorkThread[i] = ::CreateThread(NULL, 0, WorkerThread, NULL, 0, &id);
	}

	m_hIOCP = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);

	while (1)
	{
		SOCKET client;
		SOCKADDR_IN clientaddr;
		int AddrLen = sizeof(clientaddr);
		client = accept(Listensock, (sockaddr*)&clientaddr, &AddrLen);
		if (client != SOCKET_ERROR)
		{
			char ip[256] = { 0, };
			printf("%s, %d\n", inet_ntop(AF_INET, &clientaddr.sin_addr, ip, sizeof(ip)), ntohs(clientaddr.sin_port));

			user.sock = client;

			::CreateIoCompletionPort((HANDLE)client, m_hIOCP, (ULONG_PTR)&user/*완료키*/, 0);

			DWORD trans, flag = 0;

			user.ov.flag = RECV;
			int iRet = WSARecv(client, &user.buffer, 1, &trans, &flag, (LPOVERLAPPED)&user.ov, NULL);
			if (iRet == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSA_IO_PENDING)
				{

				}
			}
		}

	}

	closesocket(Listensock);
	EndWinSock();
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
DWORD WINAPI WorkerThread(LPVOID arg)
{
	LPOVERLAPPED ov;
	DWORD byteTransfer;
	ULONG_PTR keyValue;
	while (1)
	{
		// IOCP QUEUE
		BOOL bRet = ::GetQueuedCompletionStatus(m_hIOCP, &byteTransfer, &keyValue, &ov, INFINITE);
		User * pUser = (User*)keyValue;
		LPOVERLAPPED_EX ovex = (LPOVERLAPPED_EX)ov;
		if (bRet == TRUE)
		{
			if (ovex->flag == RECV)
			{
				DWORD trans = byteTransfer;
				user.ov.flag = SEND;
				int iRet = WSASend(pUser->sock, &pUser->buffer, 1, &trans, 0, &pUser->ov, NULL);
			}
			else
			{

			}
			
			//	if (keyValue == (ULONG_PTR)iocp->m_hFileRead)
			//	{
			//		iocp->DispatchRead(byteTransfer);
			//	}
			//	else
			//	{
			//		iocp->DispatchWrite(byteTransfer);
			//	}
			//}
			//else
			//{
			//	if (GetLastError() == WAIT_TIMEOUT)
			//	{
			//		continue;
			//	}
			//	if (GetLastError() == ERROR_HANDLE_EOF)
			//	{
			//		iocp->m_bEnd = true;
			//		continue;

			//	}
			//	// Error 부분
			//}
		}
	}
	return 0;
}