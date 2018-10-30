#include "Server.h"
#include "Synchronize.h"
#include "IOCP.h"

using namespace PacketUtil;

std::istream& operator >> (std::istream& is, MENU& type)
{
	int num;
	is >> num;
	type = static_cast<MENU>(num);
	return is;
}

bool isExit = false;
CRITICAL_SECTION SrvUtil::mCs;
std::vector<std::string> SrvUtil::mThreadName;

Server::Server()
{

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
void Server::Run()
{
	mAcceptor.CreateThreadandRun();
	mServerModel->Run();
	ChatRun();
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
		WaitForSingleObject(mMutex, INFINITE);
		Synchronize(this);
		UserPtr user = std::make_shared<User>(clntSock, clntAdr);
		mUserList.push_back(user);
		mServerModel->AddUser(user.get());
		DWORD Transfer;
		UPACKET packet = (Packet(PACKET_CHAT_NAME_REQ) << "ID를 입력하세요.(6자 이상 20자 이하)\n").getPacket();
		CopyMemory(user->mBuf, &packet, packet.ph.len);
		user->mWsaBuf.len = packet.ph.len;
		user->mOverlappedex.mioState = IOState::SEND;
		WSASend(user->mUserSock, &user->mWsaBuf, 1, &Transfer, 0, &user->mOverlappedex.mOverlapped, nullptr);
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
	u_short port;
	while (1)
	{
		std::cout << "포트번호를 입력하세요(1024 ~ 49151): ";
		std::cin >> port;
		if (port <= 1024 || port > 49151)
		{
			system("cls");
			std::cout << "잘못된 번호입니다." << std::endl;
		}
		else
		{
			system("cls");
			return port;
		}
	}
}
void Server::ChatRun()
{
	while (!isExit)
	{
		MENU Select = MENU::USERINFO;
		std::cout << "[채팅서버 프로그램]" << std::endl;
		std::cout << "1.접속한 유저 보기" << std::endl;
		std::cout << "2.유저 추방" << std::endl;
		std::cout << "0.서버 종료" << std::endl;
		std::cout << "입력: ";
		std::cin >> Select;
		switch (Select)
		{
		case MENU::USERINFO:
		{
			ShowUser();
		}break;
		case MENU::USERBAN:
		{
			UserBan();
		}break;
		case MENU::SERVERQUIT:
		{
			isExit = true;
		}break;
		default:
		{
			system("cls");
			std::cout << "잘못된 입력입니다." << std::endl;
		}	break;
		}
	}
}
void Server::ShowUser()
{
	system("cls");
	std::cout.width(12); std::cout << "ID"; std::cout.width(20);std::cout << "PORT"; std::cout.width(16);std::cout << "IP" << std::endl;
	std::cout.fill('='); std::cout.width(55); std::cout << " " << std::endl;
	std::cout.fill(' ');
	WaitForSingleObject(mMutex, INFINITE);
	UserIter iter = mUserList.begin();
	for (;iter != mUserList.end(); ++iter)
	{
		char IPAddr[INET_ADDRSTRLEN];
		InetNtopA(AF_INET, &((*iter)->mUserAdr.sin_addr), IPAddr, INET_ADDRSTRLEN);
		std::cout.width(21); std::cout << (*iter)->mUserID; std::cout.width(12); std::cout << ntohs((*iter)->mUserAdr.sin_port); std::cout.width(20); std::cout << IPAddr << std::endl;
	}
	std::cout << "총 유저: " << mUserList.size() << "명" << std::endl;
	ReleaseMutex(mMutex);
}
void Server::UserBan()
{
	system("cls");
	bool isUpper = false;
	std::string Msg;
	while (!isUpper)
	{
		ShowUser();
		int iSelect = 0;
		char IPAddr[INET_ADDRSTRLEN];
		std::cout << Msg << std::endl;
		Msg.clear();
		std::cout << "1.ID로 검색, 2.Port번호로 검색, 3.IP로 검색, 0.뒤로가기" << std::endl;
		std::cout << "입력: ";
		std::cin >> iSelect;
		switch (iSelect)
		{
			case 1:
			{
				User * pUser = SearchByID(IPAddr);
				if (pUser == nullptr)
				{
					system("cls");
					Msg = "해당하는 ID가 존재하지 않습니다.";
				}
				else
				{
					RemoveUser(pUser);
					mBanIP.push_back(IPAddr);
					Msg = "정상처리 되었습니다.";
				}
			}break;
			case 2:
			{
				User * pUser = SearchByPort(IPAddr);
				if (pUser == nullptr)
				{
					system("cls");
					Msg = "해당하는 포트번호가 존재하지 않습니다.";
				}
				else
				{
					RemoveUser(pUser);
					mBanIP.push_back(IPAddr);
					Msg = "정상처리 되었습니다.";
				}
			}break;
			case 3:
			{
				User * pUser = SearchByIP(IPAddr);
				if (pUser == nullptr)
				{
					system("cls");
					Msg = "해당하는 ID가 존재하지 않습니다.";
				}
				else
				{
					RemoveUser(pUser);
					mBanIP.push_back(IPAddr);
					Msg = "정상처리 되었습니다.";
				}
			}break;
			case 0:
			{
				system("cls");
				isUpper = true;
			}break;
			default:
			{
				Msg = "잘못된 입력입니다.";
			}break;
		}
	}
}
User* Server::SearchByID(char * IPAddr)
{
	std::string SearchID;
	std::cout << "검색할 ID를 입력하세요." << std::endl;
	std::cout << "입력: "; std::cin >> SearchID;
	auto Search = [SearchID, &IPAddr](const UserPtr& rhs)
	{
		InetNtopA(AF_INET, &rhs->mUserAdr.sin_addr, IPAddr, INET_ADDRSTRLEN);
		if (SearchID == rhs->mUserID)
		{
			return true;
		}
		return false;
	};
	WaitForSingleObject(mMutex, INFINITE);
	UserIter iter = std::find_if(mUserList.begin(), mUserList.end(), Search);
	if (iter == mUserList.end())
	{
		return nullptr;
	}
	ReleaseMutex(mMutex);
	return (*iter).get();
}
User* Server::SearchByPort(char * IPAddr)
{
	u_short port;
	std::cout << "검색할 포트번호를 입력하세요." << std::endl;
	std::cout << "입력: "; std::cin >> port;
	auto Search = [port, &IPAddr](const UserPtr& rhs)
	{
		InetNtopA(AF_INET, &rhs->mUserAdr.sin_addr, IPAddr, INET_ADDRSTRLEN);
		if (port == ntohs(rhs->mUserAdr.sin_port))
		{
			return true;
		}
		return false;
	};
	WaitForSingleObject(mMutex, INFINITE);
	UserIter iter = std::find_if(mUserList.begin(), mUserList.end(), Search);
	if (iter == mUserList.end())
	{
		return nullptr;
	}
	ReleaseMutex(mMutex);
	return (*iter).get();
}
User* Server::SearchByIP(char * IPAddr)
{
	std::string SearchIP;
	std::cout << "검색할 IP를 입력하세요." << std::endl;
	std::cout << "입력: "; std::cin >> SearchIP;
	auto Search = [SearchIP, &IPAddr](const UserPtr& rhs)
	{
		InetNtopA(AF_INET, &rhs->mUserAdr.sin_addr, IPAddr, INET_ADDRSTRLEN);
		if (SearchIP == IPAddr)
		{
			return true;
		}
		return false;
	};
	WaitForSingleObject(mMutex, INFINITE);
	UserIter iter = std::find_if(mUserList.begin(), mUserList.end(), Search);
	if (iter == mUserList.end())
	{
		return nullptr;
	}
	ReleaseMutex(mMutex);
	return (*iter).get();
}