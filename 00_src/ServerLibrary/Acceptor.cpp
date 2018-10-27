#include "Acceptor.h"
#include "SrvUtil.h"
#include "Server.h"

Acceptor::Acceptor(Server * server) : mServer(server)
{

}
Acceptor::~Acceptor()
{
	closesocket(mlistenSock);
}

bool Acceptor::setIPAndPort(u_short port, const TCHAR * IPAddr = nullptr)
{
	int iRet;
	mlistenSock = socket(AF_INET, SOCK_STREAM, 0);
	if (mlistenSock == INVALID_SOCKET)
	{
		SrvUtil::ErrorMsg(_T("socket Error"));
		return false;
	}

	SOCKADDR_IN sockAdr;
	ZeroMemory(&sockAdr, sizeof(sockAdr));
	sockAdr.sin_family = AF_INET;
	sockAdr.sin_port = htons(port);
	if (IPAddr != nullptr)
	{
		InetPton(AF_INET, IPAddr, &sockAdr.sin_addr);
	}
	else
		sockAdr.sin_addr.s_addr = htonl(INADDR_ANY);

	iRet = bind(mlistenSock, (SOCKADDR*)&sockAdr, sizeof(sockAdr));
	if (iRet == SOCKET_ERROR)
	{
		SrvUtil::ErrorMsg(_T("Bind Error"));
		return false;
	}
	
	iRet = listen(mlistenSock, SOMAXCONN);
	if (iRet == SOCKET_ERROR)
	{
		SrvUtil::ErrorMsg(_T("Listen Error"));
		return false;
	}
	CreateThread();
	return true;
}
bool Acceptor::Run()
{
	int iRet;
	SOCKET clntSock;
	SOCKADDR_IN clntAdr;
	int clntAdrSz = sizeof(clntAdr);
	
	mAcceptEvent = WSACreateEvent();
	WSAEventSelect(mlistenSock, mAcceptEvent, FD_ACCEPT);

	while (!mServer->isExit())
	{
		DWORD dwRet;
		dwRet = WSAWaitForMultipleEvents(1, &mAcceptEvent, true, 100, false);
		if (dwRet == WSA_WAIT_TIMEOUT || dwRet == WSA_WAIT_FAILED)
		{
			continue;
		}
		WSANETWORKEVENTS networkEvent;
		WSAEnumNetworkEvents(mlistenSock, mAcceptEvent, &networkEvent);
		if (networkEvent.iErrorCode[FD_ACCEPT_BIT] != 0)
		{
			SrvUtil::ErrorMsg(_T("Accept Error"));
			continue;
		}
		ZeroMemory(&clntAdr, sizeof(clntAdr));
		accept(clntSock, (SOCKADDR*)&clntAdr, &clntAdrSz);
		mServer->AddUser(clntSock, clntAdr);
	}
	return true;
}