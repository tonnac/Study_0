#include "Acceptor.h"
#include "SrvUtil.h"
#include "Server.h"

Acceptor::Acceptor(Server * server) : mServer(server)
{

}
Acceptor::~Acceptor()
{
}
HANDLE Acceptor::CreateThreadandRun()
{
	EnterCriticalSection(&SrvUtil::mCs);
	SrvUtil::mThreadName.push_back("Accept");
	LeaveCriticalSection(&SrvUtil::mCs);
	return Thread::CreateThreadandRun();
}
bool Acceptor::setIPAndPort(u_short port, const TCHAR * IPAddr)
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
	return true;
}
void Acceptor::Release()
{
	closesocket(mlistenSock);
	EnterCriticalSection(&SrvUtil::mCs);
	std::vector<std::string>::iterator iter;
	iter = std::find(SrvUtil::mThreadName.begin(), SrvUtil::mThreadName.end(), std::string("Accept"));
	if (iter != SrvUtil::mThreadName.end())
		SrvUtil::mThreadName.erase(iter);
	LeaveCriticalSection(&SrvUtil::mCs);
	WaitForSingleObject(mhThread, INFINITE);
}
bool Acceptor::Run()
{
	SOCKET clntSock;
	SOCKADDR_IN clntAdr;
	int clntAdrSz = sizeof(clntAdr);
	
	mAcceptEvent = WSACreateEvent();
	WSAEventSelect(mlistenSock, mAcceptEvent, FD_ACCEPT);

	while (!isExit)
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
		clntSock = accept(mlistenSock, (SOCKADDR*)&clntAdr, &clntAdrSz);
		if (clntSock == INVALID_SOCKET)
		{
			continue;
		}
		mServer->AddUser(clntSock, clntAdr);
	}
	return true;
}