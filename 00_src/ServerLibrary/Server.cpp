#include "Server.h"
#include "Synchronize.h"
#include "IOCP.h"

bool isExit = false;
CRITICAL_SECTION SrvUtil::mCs;
std::vector<std::string> SrvUtil::mThreadName;

Server::Server()
{

}

Server::~Server()
{
	mAcceptor.Release();
	mServerModel->Release();
	WSACleanup();
	DeleteCriticalSection(&SrvUtil::mCs);
	CloseHandle(mMutex);
}

void Server::Initialize()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	InitializeCriticalSection(&SrvUtil::mCs);
	mMutex = CreateMutex(nullptr, FALSE, nullptr);
	mAcceptor.setIPAndPort(12347);

	mServerModel = std::make_shared<IOCP>();
	mServerModel->Initialize();
}
void Server::Run()
{
	mAcceptor.CreateThreadandRun();
	mServerModel->Run();
}
void Server::AddUser(const SOCKET& clntSock, const SOCKADDR_IN clntAdr)
{
	{
		WaitForSingleObject(mMutex, INFINITE);
		Synchronize(this);
		UserPtr user = std::make_shared<User>(clntSock, clntAdr);
		mUserList.push_back(user);
		mServerModel->AddUser(user.get());
		DWORD Transfer, flag = 0;
		WSARecv(user->mUserSock, &user->mWsaBuf, 1, &Transfer, &flag, &user->mOverlappedex.mOverlapped, nullptr);
		ReleaseMutex(mMutex);
	}
}
void Server::RemoveUser(User* user)
{
	{
		WaitForSingleObject(mMutex, INFINITE);
		UserIter iter = std::find_if(mUserList.begin(), mUserList.end(), UserPred(user));
		if (iter != mUserList.end())
		{
			char IPAddr[INET_ADDRSTRLEN];
			InetNtopA(AF_INET, &user->mUserAdr.sin_addr, IPAddr, INET_ADDRSTRLEN);
			std::cout << "[ID: " << user->mUserID << ", IP: " << IPAddr << ", Port: " << ntohs(user->mUserAdr.sin_port) << "] Disconnect" << std::endl;
			mUserList.erase(iter);
		}
		ReleaseMutex(mMutex);
	}
}

void Server::ProcessPacket()
{
	{
		WaitForSingleObject(mMutex, INFINITE);

		int retVal;
		PACKET_ITER iter;
		for (iter = mStreamPacket.PacketBegin(); iter != mStreamPacket.PacketEnd(); ++iter)
		{
			LPTPACKET tPacket = &(*iter);
			UPACKET* pPacket = &(tPacket->mPacket);

			switch (pPacket->ph.type)
			{
				case PACKET_CHAT_MSG:
				{
					UserIter iter;
					for (iter = mUserList.begin(); iter != mUserList.end(); ++iter)
					{
						User* pUser = (*iter).get();

						if (SendPacket(pUser, tPacket->mPacket) <= 0)
						{
							break;
						}
					}
				}break;
			}
		}
		mStreamPacket.PacketClear();
		ReleaseMutex(mMutex);
	}
}
void Server::AddPacket(const TPACKET& pack)
{
	WaitForSingleObject(mMutex, INFINITE);
	mStreamPacket.AddPacket(pack);
	ReleaseMutex(mMutex);
}
int Server::SendPacket(User* pUser, const UPACKET& packetMsg)
{
	pUser->mWsaBuf.buf = (char*)&packetMsg;
	pUser->mWsaBuf.len = packetMsg.ph.len;
	pUser->mOverlappedex.mioState = IOState::SEND;
	DWORD dwSendByte = packetMsg.ph.len;

	int iRet = WSASend(pUser->mUserSock, &pUser->mWsaBuf, 1, &dwSendByte, 0, &pUser->mOverlappedex.mOverlapped, nullptr);
	if (iRet == SOCKET_ERROR)
	{
		SrvUtil::ErrorMsg(_T("SendPacket()"));
		return 0;
	}
	return 1;
}