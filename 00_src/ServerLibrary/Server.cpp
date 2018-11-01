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

	mServerModel = ServerModel::CreateServerModel(IOMODEL::IOCP);
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
void Server::AddInfo(User * pUser, P_UPACKET pPacket, DWORD flag)
{
	std::string temp;
	if (flag & ADD_ID)
	{
		temp = pUser->mUserID + " : " + std::string(pPacket->msg);
	}
	if (flag & ADD_TIME)
	{
		time_t mTime = time(nullptr);
		struct tm lt;
		localtime_s(&lt, &mTime);
		char timestr[256] = { 0, };
		strftime(timestr, 256, "%I:%M:%S", &lt);
		std::string temp1 = temp;
		temp = "[" + std::string(timestr) + "] " + temp1;
	}
	UPACKET packet = (Packet(PACKET_CHAT_MSG) << temp).getPacket();
	*pPacket = packet;
}
void Server::AddUser(const SOCKET& clntSock, const SOCKADDR_IN clntAdr)
{
	{
		UserPtr user = std::make_shared<User>(clntSock, clntAdr);
		WaitForSingleObject(mMutex, INFINITE);
		mUserList.push_back(user);
		mServerModel->AddUser(user.get());
		ReleaseMutex(mMutex);
		UPACKET packet = (Packet(PACKET_CHAT_NAME_REQ) << "ID를 입력하세요.(6자 이상 20자 이하)\n").getPacket();
		SendPacket(user.get(), packet);
	}
}
void Server::RemoveUser(User* user)
{
	{
		WaitForSingleObject(mMutex, INFINITE);
		UserIter iter = std::find_if(mUserList.begin(), mUserList.end(), UserPred(user));
		if (iter != mUserList.end())
		{
			char buf[256] = { 0, };
			sprintf_s(buf, 256, "%s님이 나가셨습니다.", user->mUserID.data());
			TPACKET tpacket;
			UPACKET packet = (PacketUtil::Packet(PACKET_LEAVE) << buf).getPacket();
			tpacket.mPacket = packet;
			tpacket.mUser = user;
			S_Server->AddPacket(tpacket);
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
				case PACKET_LEAVE:
				case PACKET_CHAT_MSG:
				{
					UserIter useriter;
					for (useriter = mUserList.begin(); useriter != mUserList.end(); ++useriter)
					{
						User* pUser = (*useriter).get();
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
					UPACKET packet;
					bool isExist = false;
					User * pUser = tPacket->mUser;
					if (strlen(pPacket->msg) < 6 || strlen(pPacket->msg) > 20)
					{
						packet = (Packet(PACKET_CHAT_NAME_REQ) << "ID의 길이는 6자 이상 20자 이하로 정해주세요.\n").getPacket();
					}
					else
					{
						UserIter useriter;
						for (useriter = mUserList.begin(); useriter != mUserList.end(); ++useriter)
						{
							std::string UserName = (*useriter)->mUserID;
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
					SendPacket(pUser, packet);
				}break;
			}
		}
		mStreamPacket.PacketClear();
		ReleaseMutex(mMutex);
	}
}
void Server::AddPacket(TPACKET& pack)
{
	WaitForSingleObject(mMutex, INFINITE);
	if (pack.mPacket.ph.type == PACKET_CHAT_MSG)
	{
		AddInfo(pack.mUser, &pack.mPacket, ADD_TIME | ADD_ID);
	}
	if (pack.mPacket.ph.type == PACKET_ENTER)
	{
		char buf[256] = { 0, };
		sprintf_s(buf, sizeof(buf), "%s님이 입장하였습니다", pack.mUser->mUserID.data());
		UPACKET _packet = (Packet(PACKET_CHAT_MSG) << buf).getPacket();
		CopyMemory(&pack.mPacket, &_packet, sizeof(UPACKET));
	}
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
	CopyMemory(pUser->mBuf, &packetMsg, packetMsg.ph.len);
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