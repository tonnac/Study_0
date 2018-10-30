#include "Server.h"
#include "Synchronize.h"
#include "IOCP.h"

using namespace PacketUtil;

bool isExit = false;
CRITICAL_SECTION SrvUtil::mCs;
std::vector<std::string> SrvUtil::mThreadName;

Server * Server::mServer = nullptr;

Server::Server()
{
	if (mServer == nullptr)
		mServer = this;
}

Server::~Server()
{
	mUserList.clear();
	mAcceptor.Release();
	mServerModel->Release();
	WSACleanup();
	DeleteCriticalSection(&SrvUtil::mCs);
	CloseHandle(mMutex);
	system("cls");
	std::cout << "서버가 종료되었습니다. 아무키나 누르세요." << std::endl;
	_getch();
}

void Server::Initialize()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	u_short port = PortSet();

	InitializeCriticalSection(&SrvUtil::mCs);
	mMutex = CreateMutex(nullptr, FALSE, nullptr);
	mAcceptor.setIPAndPort(port);

	mServerModel = std::make_shared<IOCP>();
	mServerModel->Initialize();
}
void Server::ServerRun()
{
	mAcceptor.CreateThreadandRun();
	mServerModel->Run();
	Run();
}
void Server::Run()
{
	return;
}
void Server::AddID(User * pUser, P_UPACKET pPacket)
{
	std::string temp = "[" + pUser->mUserID + "] : " + std::string(pPacket->msg);
	UPACKET packet = (Packet(PACKET_CHAT_MSG) << temp).getPacket();
	*pPacket = packet;
}
void Server::AddUser(const SOCKET& clntSock, const SOCKADDR_IN clntAdr)
{
	{
		UserPtr user = std::make_shared<User>(clntSock, clntAdr);
		WaitForSingleObject(mMutex, INFINITE);
		mUserList.push_back(user);
		ReleaseMutex(mMutex);
		mServerModel->AddUser(user.get());
		DWORD Transfer;
		UPACKET packet = (Packet(PACKET_CHAT_NAME_REQ) << "ID를 입력하세요.(6자 이상 20자 이하)\n").getPacket();
		CopyMemory(user->mBuf, &packet, packet.ph.len);
		user->mWsaBuf.len = packet.ph.len;
		user->mOverlappedex.mioState = IOState::SEND;
		WSASend(user->mUserSock, &user->mWsaBuf, 1, &Transfer, 0, &user->mOverlappedex.mOverlapped, nullptr);
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
	//		std::cout << "[ID: " << user->mUserID << ", IP: " << IPAddr << ", Port: " << ntohs(user->mUserAdr.sin_port) << "] Disconnect" << std::endl;
			mUserList.erase(iter);
		}
		ReleaseMutex(mMutex);
	}
}

void Server::ProcessPacket()
{
	{
		WaitForSingleObject(mMutex, INFINITE);

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
						if (pUser->misActive == true)
						{
							if (SendPacket(pUser, tPacket->mPacket) <= 0)
							{
								break;
							}
						}
					}
				}break;
				case PACKET_CHAT_NAME_ACK:
				{
					DWORD SendByte;
					UPACKET packet;
					bool isExist = false;
					User * pUser = tPacket->mUser;
					if (strlen(pPacket->msg) < 6 || strlen(pPacket->msg) > 20)
					{
						packet = (Packet(PACKET_CHAT_NAME_REQ) << "ID의 길이는 6자 이상 20자 이하로 정해주세요.\n").getPacket();
					}
					else
					{
						UserIter iter;
						for (iter = mUserList.begin(); iter != mUserList.end(); ++iter)
						{
							std::string UserName = (*iter)->mUserID;
							if (!_stricmp(UserName.data(), pPacket->msg))
							{
								isExist = true;
								break;
							}
						}
						if (isExist == true)
						{
							packet = (Packet(PACKET_CHAT_NAME_REQ) << "해당하는 ID가 존재합니다. 다시 입력해주세요.\n").getPacket();
						}
						else
						{
							char buf[256] = { 0, };
							sprintf_s(buf, sizeof(buf), "환영합니다 %s님\n", pPacket->msg);
							packet = (Packet(PACKET_CHAT_MSG) << buf).getPacket();
							pUser->mUserID.append(pPacket->msg);
							pUser->misActive = true;
						}
					}
					CopyMemory(tPacket->mUser->mBuf, &packet, packet.ph.len);
					pUser->mWsaBuf.len = packet.ph.len;
					pUser->mOverlappedex.mioState = IOState::SEND;
					WSASend(pUser->mUserSock, &pUser->mWsaBuf, 1, &SendByte, 0,
						&pUser->mOverlappedex.mOverlapped, nullptr);
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
	if(pack.mPacket.ph.type == PACKET_CHAT_MSG)
		AddID(pack.mUser, const_cast<P_UPACKET>(&pack.mPacket));
	mStreamPacket.AddPacket(pack);
	ReleaseMutex(mMutex);
}
bool Server::CheckUser(const std::string& IPaddr)
{
	auto SearchIP = [IPaddr](const std::string rhs) 
	{
		if (rhs == IPaddr)
		{
			return true;
		}
		return false;
	};
	std::vector<std::string>::iterator iter;
	iter = std::find_if(mBanIP.begin(), mBanIP.end(), SearchIP);
	if (iter != mBanIP.end())
	{
		return false;
	}
	return true;
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
u_short	Server::PortSet()
{
	return 1;
}