#include "ChatServer.h"

std::istream& operator >> (std::istream& is, MENU& type)
{
	int num;
	is >> num;
	type = static_cast<MENU>(num);
	return is;
}

u_short	ChatServer::PortSet()
{
	u_short port;
	while (1)
	{
		std::cout << "��Ʈ��ȣ�� �Է��ϼ���(1024 ~ 49151): ";
		std::cin >> port;
		if (port <= 1024 || port > 49151)
		{
			system("cls");
			std::cout << "�߸��� ��ȣ�Դϴ�." << std::endl;
		}
		else
		{
			system("cls");
			return port;
		}
	}
}
void ChatServer::Run()
{
	while (!isExit)
	{
		MENU Select = MENU::USERINFO;
		std::cout << "[ä�ü��� ���α׷�]" << std::endl;
		std::cout << "1.������ ���� ����" << std::endl;
		std::cout << "2.���� �߹�" << std::endl;
		std::cout << "0.���� ����" << std::endl;
		std::cout << "�Է�: ";
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
			std::cout << "�߸��� �Է��Դϴ�." << std::endl;
		}	break;
		}
	}
}
void ChatServer::ShowUser()
{
	system("cls");
	std::cout.width(12); std::cout << "ID"; std::cout.width(20); std::cout << "PORT"; std::cout.width(16); std::cout << "IP" << std::endl;
	std::cout.fill('='); std::cout.width(55); std::cout << " " << std::endl;
	std::cout.fill(' ');
	WaitForSingleObject(mMutex, INFINITE);
	UserIter iter = mUserList.begin();
	for (; iter != mUserList.end(); ++iter)
	{
		char IPAddr[INET_ADDRSTRLEN];
		InetNtopA(AF_INET, &((*iter)->mUserAdr.sin_addr), IPAddr, INET_ADDRSTRLEN);
		std::cout.width(21); std::cout << (*iter)->mUserID; std::cout.width(12); std::cout << ntohs((*iter)->mUserAdr.sin_port); std::cout.width(20); std::cout << IPAddr << std::endl;
	}
	std::cout << "�� ����: " << mUserList.size() << "��" << std::endl;
	ReleaseMutex(mMutex);
}
void ChatServer::UserBan()
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
		std::cout << "1.ID�� �˻�, 2.Port��ȣ�� �˻�, 3.IP�� �˻�, 0.�ڷΰ���" << std::endl;
		std::cout << "�Է�: ";
		std::cin >> iSelect;
		switch (iSelect)
		{
		case 1:
		{
			User * pUser = SearchByID(IPAddr);
			if (pUser == nullptr)
			{
				system("cls");
				Msg = "�ش��ϴ� ID�� �������� �ʽ��ϴ�.";
			}
			else
			{
				RemoveUser(pUser);
				mBanIP.push_back(IPAddr);
				Msg = "����ó�� �Ǿ����ϴ�.";
			}
		}break;
		case 2:
		{
			User * pUser = SearchByPort(IPAddr);
			if (pUser == nullptr)
			{
				system("cls");
				Msg = "�ش��ϴ� ��Ʈ��ȣ�� �������� �ʽ��ϴ�.";
			}
			else
			{
				RemoveUser(pUser);
				mBanIP.push_back(IPAddr);
				Msg = "����ó�� �Ǿ����ϴ�.";
			}
		}break;
		case 3:
		{
			User * pUser = SearchByIP(IPAddr);
			if (pUser == nullptr)
			{
				system("cls");
				Msg = "�ش��ϴ� ID�� �������� �ʽ��ϴ�.";
			}
			else
			{
				RemoveUser(pUser);
				mBanIP.push_back(IPAddr);
				Msg = "����ó�� �Ǿ����ϴ�.";
			}
		}break;
		case 0:
		{
			system("cls");
			isUpper = true;
		}break;
		default:
		{
			Msg = "�߸��� �Է��Դϴ�.";
		}break;
		}
	}
}
User* ChatServer::SearchByID(char * IPAddr)
{
	std::string SearchID;
	std::cout << "�˻��� ID�� �Է��ϼ���." << std::endl;
	std::cout << "�Է�: "; std::cin >> SearchID;
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
User* ChatServer::SearchByPort(char * IPAddr)
{
	u_short port;
	std::cout << "�˻��� ��Ʈ��ȣ�� �Է��ϼ���." << std::endl;
	std::cout << "�Է�: "; std::cin >> port;
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
User* ChatServer::SearchByIP(char * IPAddr)
{
	std::string SearchIP;
	std::cout << "�˻��� IP�� �Է��ϼ���." << std::endl;
	std::cout << "�Է�: "; std::cin >> SearchIP;
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

int main()
{
	ChatServer svr;
	svr.Initialize();
	svr.ServerRun();
	return 0;
}