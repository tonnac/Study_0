#include "Server.h"
#include "Synchronize.h"
#include "IOCP.h"

using namespace PacketUtil;

bool isExit = false;
CRITICAL_SECTION SrvUtil::mCs;
std::vector<std::string> SrvUtil::mThreadName;

Server * Server::mServer = nullptr;

UINT WINAPI Server::ConnectDB(LPVOID arg)
{
	Server* pServer = (Server*)arg;
	pServer->mSql.Initialize();
	return 1;
}

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
	mSql.Release();
	system("cls");
	std::cout << "서버가 종료되었습니다. 아무키나 누르세요." << std::endl;
	_getch();
}

bool Server::Initialize()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	
	u_short port = PortSet();

	InitializeCriticalSection(&SrvUtil::mCs);
	mMutex = CreateMutex(nullptr, FALSE, nullptr);
	mAcceptor.setIPAndPort(port);

	mServerModel = ServerModel::CreateServerModel(IOMODEL::IOCP);
	mServerModel->Initialize();
	HANDLE DBConnect = (HANDLE)_beginthreadex(nullptr, 0, ConnectDB, (LPVOID)this, 0, nullptr);
	int Cnt = 0;
	while (true)
	{
		DWORD dwRet = WaitForSingleObject(DBConnect, 1000);
		if (dwRet == WAIT_OBJECT_0)
			break;
		else
		{
			++Cnt;
			std::cout.width(100); std::cout.fill(' '); std::cout << '\r';
			std::cout << "연결중";
			for (int i = 0; i < Cnt; ++i)
			{
				std::cout << ".";
			}
			if (Cnt >= 5)
			{
				MessageBox(nullptr, L"데이터베이스와 연결이 되지않습니다.", L"Error", MB_ICONERROR);
				return false;
			}
		}
	}
	return true;
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
		char IPAddr[INET_ADDRSTRLEN];
		ReleaseMutex(mMutex);
		//UPACKET packet = (Packet(PACKET_CHAT_NAME_REQ) << "ID를 입력하세요.(6자 이상 20자 이하)\n").getPacket();
		//SendPacket(user.get(), packet);
	}
}

void Server::EditID(const std::string& befUserID, const std::string& aftUserID)
{
	{
		WaitForSingleObject(mMutex, INFINITE);
		UserIter iter = mUserList.begin();
		for (;iter != mUserList.end(); ++iter)
		{
			User * pUser = (User*)&iter;
			if (pUser->mUserID == befUserID)
			{
				pUser->mUserID = aftUserID;
			}
		}
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
			char buf[256] = { 0, };
			sprintf_s(buf, 256, "%s님이 나가셨습니다.", user->mUserID.data());
			TPACKET tpacket;
			UPACKET packet = (PacketUtil::Packet(PACKET_LEAVE) << buf).getPacket();
			tpacket.mPacket = packet;
			tpacket.mUser = user;
			mSql.Logout(user->mUserID);
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

				case PACKET_ID_CREATE:
				{
					UPACKET packet;
					User * pUser = tPacket->mUser;

					std::string ID;
					std::string packetmsg = packet.msg;
					ID.assign(packetmsg, 0, packetmsg.find_first_of('\n'));

					if (!mSql.SearchUser(ID))
					{
						packet = (Packet(PACKET_ID_EXIST) << "해당하는 ID가 존재합니다. 다시 입력해주세요.\n").getPacket();
					}
					else
					{
						packet = (Packet(PACKET_CHAT_MSG) << "ID 생성이 완료됐습니다.").getPacket();
					}
					SendPacket(pUser, packet);
				}break;

				case PACKET_ID_LOGIN:
				{
					UPACKET packet;
					User * pUser = tPacket->mUser;

					std::string ID;
					std::string Password;
					std::string packetmsg = packet.msg;
					ID.assign(packetmsg, 0, packetmsg.find_first_of('\n'));
					Password.assign(packetmsg, packetmsg.find_first_of('\n') + 1, packetmsg.length());

					if (!mSql.LoginUser(ID, Password))
					{
						packet = (Packet(PACKET_ID_EXIST) << "ID 또는 비밀번호가 틀렸습니다.").getPacket();
					}
					else
					{
						char buf[256] = { 0, };
						sprintf_s(buf, sizeof(buf), "환영합니다 %s님\n", pPacket->msg);
						packet = (Packet(PACKET_CHAT_MSG) << buf).getPacket();
						pUser->mUserID.append(ID);
						pUser->misActive = true;
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