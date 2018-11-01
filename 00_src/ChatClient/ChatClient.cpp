#include "ChatClient.h"

using namespace PacketUtil;

ChatClient::ChatClient() : mQuit(FALSE)
{
	ZeroMemory(&msockAdr, sizeof(msockAdr));
	ZeroMemory(mBanMsg, sizeof(BUF_SZ));
	ZeroMemory(&mWsaOverlapped, sizeof(mWsaOverlapped));
	mWsaBuf.buf = mbuf;
	mWsaBuf.len = BUF_SZ;
	mMutex = CreateMutex(nullptr, FALSE, nullptr);
	mEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);
	mWsaOverlapped.hEvent = (HANDLE)this;
}

bool ChatClient::Initialize()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	mhSock = socket(AF_INET, SOCK_STREAM, 0);
	if (mhSock == INVALID_SOCKET)
	{
		return false;
	}
	InputIPAndPort();
	HANDLE ConnectHandle = (HANDLE)_beginthreadex(nullptr, 0, ConnectFunc, (LPVOID)this, 0, nullptr);
	int Cnt = 0;
	while(true)
	{
		DWORD dwRet = WaitForSingleObject(ConnectHandle, 1000);
		if (dwRet == WAIT_OBJECT_0)
		{
			if (mQuit == TRUE)
			{
				QuitProgram();
				return false;
			}
			break;
		}
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
				MessageBox(nullptr, L"서버와 연결이 되지않습니다.", L"Error", MB_ICONERROR);
				return false;
			}
		}
	}
	return true;
}
void ChatClient::Run()
{
	if (InputID() == false)
	{
		QuitProgram();
		return;
	}

	HANDLE ThreadHandle = (HANDLE)_beginthreadex(nullptr, 0, ThreadFunc, (LPVOID)this, 0, nullptr);
	CloseHandle(ThreadHandle);
	HANDLE ChatHandle = (HANDLE)_beginthreadex(nullptr, 0, ShowChat, (LPVOID)this, 0, nullptr);
	CloseHandle(ChatHandle);
	DWORD dwRet;
	do
	{
		SleepEx(100, TRUE);
		DWORD recvBytes, flaginfo = 0;
		int retval;
		retval = WSARecv(mhSock, &mWsaBuf, 1, &recvBytes, &flaginfo, &mWsaOverlapped, CompRoutine);
		if (retval == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSA_IO_PENDING)
			{
				SrvUtil::ErrorMsg(_T("WsaRecv()"));
				mQuit = TRUE;
				continue;
			}
		}
	} while (mQuit != TRUE);

	dwRet = WaitForSingleObject(ThreadHandle, INFINITE);
	if (dwRet == WAIT_FAILED)
	{
		std::cout << "Thread Error" << std::endl;
		return;
	}

	QuitProgram();
}
void ChatClient::InputIPAndPort()
{
	char IPAddr[INET_ADDRSTRLEN];
	u_short port;
	std::cout << "IP를 입력하세요." << std::endl;
	std::cout << "입력: ";
	std::cin.getline(IPAddr, INET_ADDRSTRLEN);
	while (1)
	{
		std::cout << "포트번호를 입력하세요(1024 ~ 49151): ";
		char portbuf[20];
		std::cin.getline(portbuf, sizeof(portbuf));
		port = std::stoi(portbuf);
		if (port > 1024 && port <= 49151)
		{
			system("cls");
			break;
		}
		else
		{
			system("cls");
			std::cout << "잘못된 번호입니다." << std::endl;
		}
	}

	msockAdr.sin_family = AF_INET;
	msockAdr.sin_port = htons(port);
	InetPtonA(AF_INET, IPAddr, &msockAdr.sin_addr);
}
void ChatClient::gotoxy(int x, int y)
{
	COORD pos = { x,y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
COORD ChatClient::getXY()
{
	COORD Cur;
	CONSOLE_SCREEN_BUFFER_INFO a;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &a);
	Cur.X = a.dwCursorPosition.X;
	Cur.Y = a.dwCursorPosition.Y;
	return Cur;
}
UINT WINAPI ChatClient::ConnectFunc(LPVOID arg)
{
	ChatClient * pClnt = (ChatClient*)arg;
	int iRet = connect(pClnt->mhSock, (SOCKADDR*)&pClnt->msockAdr, sizeof(msockAdr));
	if (iRet == SOCKET_ERROR)
	{
		SrvUtil::ErrorMsg(_T("Connect"));
		pClnt->mQuit = TRUE;
		return 1;
	}
	UPACKET packet;
	BOOL Ret = RecvPacket(pClnt->mhSock, &packet);
	if (Ret == FALSE || packet.ph.type == PACKET_BANIP)
	{
		if (packet.ph.type == PACKET_BANIP)
		{
			CopyMemory(pClnt->mBanMsg, packet.msg, packet.ph.len);
			pClnt->mQuit = TRUE;
		}
		return 1;
	}
	return 2;
}
UINT WINAPI ChatClient::ThreadFunc(LPVOID arg)
{
	static bool See = false;
	ChatClient * pClnt = (ChatClient*)arg;
	do
	{
		if (See == false)
		{
			WaitForSingleObject(pClnt->mMutex, INFINITE);
			gotoxy(0, 25);
			std::cout.width(400); std::cout.fill(' '); std::cout << '\r';
			gotoxy(0, 25);
			std::cout << "채팅 입력(Q 종료):";
			See = true;
			ReleaseMutex(pClnt->mMutex);
		}
		char chatbuf[BUF_SZ] = { 0, };
		std::cin.getline(chatbuf, sizeof(chatbuf));
		if (_stricmp(chatbuf, "q") == 0)
		{
			pClnt->mQuit = TRUE;
			continue;
		}
		if (strlen(chatbuf) > 40 || chatbuf[0] == 0)
		{
			See = false;
			continue;
		}
		int retVal = SendPacket(pClnt->mhSock, chatbuf, (int)strlen(chatbuf) + 1);
		See = false;
	} while (pClnt->mQuit != TRUE);
	return 1;
}
UINT WINAPI ChatClient::ShowChat(LPVOID arg)
{
	ChatClient * pClnt = (ChatClient*)arg;
	while (pClnt->mQuit != TRUE)
	{
		{
			WaitForSingleObject(pClnt->mEvent, INFINITE);
			pClnt->ProcessPacket();
			ResetEvent(pClnt->mEvent);
		}
	}
	return 1;
}
void CALLBACK ChatClient::CompRoutine(DWORD dwError, DWORD dwByte, LPWSAOVERLAPPED lpOverlapped, DWORD flags)
{
	static int cnt = 0;
	ChatClient* pClnt = (ChatClient*)lpOverlapped->hEvent;
	if (cnt == 0 && (dwError != 0 || dwByte == 0))
	{
		++cnt;
		std::cout << "Server Disconnect" << std::endl;
		pClnt->mQuit = TRUE;
		return;
	}
	HANDLE bufhandle = lpOverlapped->hEvent;

	pClnt->DispatchMsg(dwByte, lpOverlapped);

	lpOverlapped->hEvent = nullptr;
	ZeroMemory(pClnt->mbuf, BUF_SZ);
	ZeroMemory(lpOverlapped, sizeof(WSAOVERLAPPED));
	lpOverlapped->hEvent = bufhandle;

	if (!pClnt->mPacketList.empty())
	{
		SetEvent(pClnt->mEvent);
	}
}
bool ChatClient::InputID()
{
	UPACKET packet;
	while (1)
	{
		BOOL Ret = RecvPacket(mhSock, &packet);
		if (Ret == FALSE)
		{
			return false;
		}
		switch (packet.ph.type)
		{
			case PACKET_CHAT_NAME_REQ:
			{
				char NameBuffer[256] = { 0, };
				std::cout << packet.msg;
				std::cin.getline(NameBuffer, sizeof(NameBuffer));
				UPACKET sendpacket = (Packet(PACKET_CHAT_NAME_ACK) << NameBuffer).getPacket();
				SendPacket(mhSock, sendpacket);
			}break;
			case PACKET_CHAT_MSG:
			{
				system("cls");
				PushChat(packet.msg);
				UPACKET sendpacket = (Packet(PACKET_ENTER) << ".").getPacket();
				SendPacket(mhSock, sendpacket);
				return true;
			};
			default:
				break;
		}
	}
}
void ChatClient::ProcessPacket()
{
	std::vector<UPACKET>::iterator iter;
	for (iter = mPacketList.begin(); iter != mPacketList.end(); ++iter)
	{
		UPACKET packet = ((UPACKET)*iter);

		switch (packet.ph.type)
		{
		case PACKET_LEAVE:
		case PACKET_CHAT_MSG:
		{
			PushChat(packet.msg);
		}break;
		}
	}
	mPacketList.clear();
}
void ChatClient::ShowChat()
{
	WaitForSingleObject(mMutex, INFINITE);
	COORD pos = getXY();
	gotoxy(0, 0);
	std::list<std::string>::iterator iter;
	for (iter = mChatLog.begin(); iter != mChatLog.end(); ++iter)
	{
		std::cout.width(100); std::cout.fill(' '); std::cout << '\r';
		std::cout << *iter << std::endl;
	}
	gotoxy(pos.X, pos.Y);
	ReleaseMutex(mMutex);
}
void ChatClient::PushChat(const std::string& str)
{
	fd_set;
	if (mChatLog.size() >= 22)
	{
		mChatLog.pop_back();
	}
	mChatLog.push_front(str);
	ShowChat();
}
void ChatClient::QuitProgram()
{
	CloseHandle(mMutex);
	closesocket(mhSock);
	CloseHandle(mEvent);
	WSACleanup();
	system("cls");
	std::cout << mBanMsg << std::endl;
	std::cout << "연결이 종료되었습니다. 아무키나 누르세요." << std::endl;
	_getch();
}
void ChatClient::DispatchMsg(DWORD Trans, LPWSAOVERLAPPED lpOverlapped)
{
	static DWORD WritePos = 0;
	static DWORD ReadPos = 0;
	static DWORD StartPos = 0;
	static char Buffer[MAX_BUF_SZ] = { 0, };

	if (WritePos + Trans > MAX_BUF_SZ)
	{
		char temp[BUF_SZ];
		CopyMemory(temp, &Buffer[StartPos], ReadPos);
		ZeroMemory(Buffer, MAX_BUF_SZ);
		CopyMemory(Buffer, temp, ReadPos);
		StartPos = 0;
		WritePos = ReadPos;
	}

	CopyMemory(&Buffer[WritePos], mWsaBuf.buf, Trans);

	WritePos += Trans;
	ReadPos += Trans;

	if (ReadPos < PACKET_HEADER_SIZE) return;

	P_UPACKET Packet = (P_UPACKET)&Buffer[StartPos];

	if (ReadPos >= Packet->ph.len)
	{
		do
		{
			UPACKET addPacket;
			CopyMemory(&addPacket, Packet, Packet->ph.len);

			ReadPos -= Packet->ph.len;
			StartPos += Packet->ph.len;

			mPacketList.push_back(addPacket);

			if (ReadPos < PACKET_HEADER_SIZE)
			{
				break;
			}

			Packet = (P_UPACKET)mWsaBuf.buf;
		} while (ReadPos >= Packet->ph.len);
	}
}