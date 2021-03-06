#include "Acceptor.h"
#include "SrvUtil.h"
#include "Server.h"

using namespace PacketUtil;

Acceptor::Acceptor()
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
bool Acceptor::ClientPermission(const SOCKET& sock, const SOCKADDR_IN& sockAdr)
{
	char IPAddr[INET_ADDRSTRLEN];
	InetNtopA(AF_INET, &sockAdr.sin_addr, IPAddr, INET_ADDRSTRLEN);
	if (S_Server->CheckUser(std::string(IPAddr)) == false)
	{
		UPACKET packet = (Packet(PACKET_BANIP) << "해당 IP는 접속할수 없습니다.\n").getPacket();
		SendPacket(sock, packet);
		closesocket(sock);
		return false;
	}
	UPACKET packet = (Packet(PACKET_PERMISSION) << ".").getPacket();
	SendPacket(sock, packet);
	return true;
}
bool Acceptor::Run()
{
	SOCKET clntSock;
	SOCKADDR_IN clntAdr;
	int clntAdrSz = sizeof(clntAdr);
	while (!isExit)
	{
		ZeroMemory(&clntAdr, sizeof(clntAdr));
		clntSock = accept(mlistenSock, (SOCKADDR*)&clntAdr, &clntAdrSz);
		if (clntSock == INVALID_SOCKET)
		{
			continue;
		}
		if (!ClientPermission(clntSock, clntAdr))
		{
			continue;
		}
		S_Server->AddUser(clntSock, clntAdr);
	}
	return true;
}