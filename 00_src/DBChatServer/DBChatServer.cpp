#include "DBChatServer.h"

u_short	ChatServer::PortSet()
{
	u_short port;
	while (1)
	{
		char buf[256] = { 0, };
		std::cout << "��Ʈ��ȣ�� �Է��ϼ���(1024 ~ 49151): ";
		std::cin.getline(buf, 256);
		port = std::stoi(buf);
		if (port > 1024 && port <= 49151)
		{
			system("cls");
			return port;
		}
		else
		{
			system("cls");
			std::cout << "�߸��� ��ȣ�Դϴ�." << std::endl;
		}
	}
}
void ChatServer::Run()
{
	while (!isExit)
	{
		MENU Select = MENU::USERINFO;
		char buf[256] = { 0, };
		std::cout << "[ä�ü��� ���α׷�]" << std::endl;
		std::cout << "1.������ ���� ����" << std::endl;
		std::cout << "2.���� �߹�" << std::endl;
		std::cout << "3.�����ͺ��̽�" << std::endl;
		std::cout << "0.���� ����" << std::endl;
		std::cout << "�Է�: ";
		std::cin.getline(buf, sizeof(buf));
		Select = (MENU)std::stoi(buf);
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
		case MENU::DATABASE:
		{
			DataBase();
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
		char buf[256] = { 0, };
		char IPAddr[INET_ADDRSTRLEN];
		if (!Msg.empty())
		{
			std::cout << Msg << std::endl;
			Msg.clear();
		}
		std::cout << "1.ID�� �˻�, 2.Port��ȣ�� �˻�, 3.IP�� �˻�, 0.�ڷΰ���" << std::endl;
		std::cout << "�Է�: ";
		std::cin.getline(buf, 256);
		iSelect = std::stoi(buf);
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
	char buf[256];
	std::cout << "�˻��� ��Ʈ��ȣ�� �Է��ϼ���." << std::endl;
	std::cout << "�Է�: "; std::cin.getline(buf, 256);
	port = std::atoi(buf);
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

void ChatServer::DataBase()
{
	system("cls");
	std::string Msg;
	while (1)
	{
		int Select;
		char buf[256] = { 0, };
		if (!Msg.empty())
		{
			std::cout << Msg << std::endl;
			Msg.clear();
		}
		std::cout << "[�����ͺ��̽�]" << std::endl;
		std::cout << "1.������ ��ȸ" << std::endl;
		std::cout << "2.������ �߰�" << std::endl;
		std::cout << "3.������ ����" << std::endl;
		std::cout << "4.������ ����" << std::endl;
		std::cout << "0.�ڷ� ����" << std::endl;
		std::cout << "�Է�: ";
		std::cin.getline(buf, sizeof(buf));
		Select = std::stoi(buf);
		switch (Select)
		{
			case 1:
			{
				system("cls");
				mSql.ShowDatabase();
			}break;
			case 2:
			{
				AddDB();
			}break;
			case 3:
			{
				EditDB();
			}break;
			case 4:
			{
				DeleteDB();
			}break;
			case 0:
			{
				return;
			}break;
			default:
			{
				system("cls");
				std::cout << "�߸��� �Է��Դϴ�." << std::endl;
			}break;
		}
	}
}

void ChatServer::AddDB()
{
	std::string Msg;
	while (1)
	{
		char IDBuf[256] = { 0, };
		char PWBuf[256] = { 0, };
		system("cls");
		if (!Msg.empty())
		{
			std::cout << Msg << std::endl;
			Msg.clear();
		}
		std::cout << "ID �Է�(6~10��): ";
		std::cin.getline(IDBuf, sizeof(IDBuf));
		if (strlen(IDBuf) < 6 || strlen(IDBuf) > 10)
		{
			Msg = "ID�� 6�� �̻� 10�� ���Ͽ��� �մϴ�.";
			continue;
		}
		std::cout << "�н����� �Է�(6~10��): ";
		std::cin.getline(PWBuf, sizeof(PWBuf));
		if (strlen(PWBuf) < 6 || strlen(PWBuf) > 10)
		{
			Msg = "�н������ 6�� �̻� 10�� ���Ͽ��� �մϴ�.";
			continue;
		}
		if (!mSql.SearchUser(IDBuf))
		{
			system("cls");
			std::cout << "�ش��ϴ� ID�� �̹� �����մϴ�." << std::endl;
		}
		mSql.AddUser(IDBuf, PWBuf);
		system("cls");
		std::cout << "�����Ͱ� �߰��ƽ��ϴ�." << std::endl;
		return;
	}
}
void ChatServer::EditDB()
{
	std::string Msg;
	while (1)
	{
		system("cls");
		if (!Msg.empty())
		{
			std::cout << Msg << std::endl;
			Msg.clear();
		}
		mSql.ShowDatabase();
		char IDBuf[256] = { 0, };
		char PWBuf[256] = { 0, };
		std::cout << "�˻� ID �Է�(6~10��): ";
		std::cin.getline(IDBuf, sizeof(IDBuf));
		if (strlen(IDBuf) < 6 || strlen(IDBuf) > 10)
		{
			Msg = "ID�� 6�� �̻� 10�� ���Ͽ��� �մϴ�.";
			continue;
		}
		if (!mSql.SearchUser(std::string(IDBuf)))
		{
			Msg = "�ش��ϴ� ID�� �������� �ʽ��ϴ�.";
			continue;
		}

		if (EditUser(std::string(IDBuf)) == true)
		{
			break;
		}
	}
}
void ChatServer::DeleteDB()
{
	std::string Msg;
	while (1)
	{
		char IDBuf[256] = { 0, };
		system("cls");
		if (!Msg.empty())
		{
			std::cout << Msg << std::endl;
			Msg.clear();
		}
		std::cout << "ID �Է�(6~10��): ";
		std::cin.getline(IDBuf, sizeof(IDBuf));
		if (strlen(IDBuf) < 6 || strlen(IDBuf) > 10)
		{
			Msg = "ID�� 6�� �̻� 10�� ���Ͽ��� �մϴ�.";
			continue;
		}
		mSql.DelUser(std::string(IDBuf));
		system("cls");
		std::cout << "������ �Ϸ�ƽ��ϴ�." << std::endl;
		return;
	}
}

bool ChatServer::EditUser(const std::string ID)
{
	std::string Msg;
	while (1)
	{
		if (!Msg.empty())
		{
			std::cout << Msg << std::endl;
			Msg.clear();
		}
		int iSelect;
		char SelBuf[256] = { 0, };
		std::cout << "���� �׸��� �����ϼ���" << std::endl;
		std::cout << "1. ID" << std::endl;
		std::cout << "2. Password" << std::endl;
		std::cout << "�Է�: ";
		std::cin.getline(SelBuf, sizeof(SelBuf));
		iSelect = std::stoi(SelBuf);


		switch (iSelect)
		{
			case 1:
			{
				while (1)
				{
					if (!Msg.empty())
					{
						std::cout << Msg << std::endl;
						Msg.clear();
					}
					char aftID[256] = { 0, };
					std::cout << "������ ID�Է�: ";
					std::cin.getline(aftID, sizeof(aftID));
					if (strlen(aftID) < 6 || strlen(aftID) > 10)
					{
						Msg = "ID�� 6�� �̻� 10�� ���Ͽ��� �մϴ�.";
						continue;
					}
					mSql.EditUser(ID, std::string(aftID));
					EditID(ID, std::string(aftID));
					system("cls");
					std::cout << "ID ������ �Ϸ�ƽ��ϴ�" << std::endl;
					return true;
				}
			}break;

			case 2:
			{
				while (1)
				{
					if (!Msg.empty())
					{
						std::cout << Msg << std::endl;
						Msg.clear();
					}
					char aftPass[256] = { 0, };
					std::cout << "������ �н����� �Է�: ";
					std::cin.getline(aftPass, sizeof(aftPass));
					if (strlen(aftPass) < 6 || strlen(aftPass) > 10)
					{
						Msg = "�н������ 6�� �̻� 10�� ���Ͽ��� �մϴ�.";
						continue;
					}
					mSql.EditPassword(ID, std::string(aftPass));
					system("cls");
					std::cout << "�н����� ������ �Ϸ�ƽ��ϴ�" << std::endl;
					return true;
				}
			}break;

			default:
			{
				system("cls");
				Msg = "�߸��� �Է��Դϴ�.";
			}break;
		}
	}
}

int main()
{
	ChatServer svr;
	if (!svr.Initialize())
	{
		return -1;
	}
	svr.ServerRun();
	return 0;
}