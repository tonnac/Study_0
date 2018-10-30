#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <process.h>
#include <conio.h>
#include <vector>
#include "Protocol.h"
#include "SrvUtil.h"

#pragma comment(lib, "ws2_32")

using namespace PacketUtil;

namespace GlobalVal
{
	std::vector<UPACKET> packetList;
	BOOL Quit;
	char buf[BUF_SZ];
	char BanMsg[BUF_SZ];
	std::list<std::string> ChatLog;
	HANDLE gMutex;
}

UINT WINAPI ThreadFunc(LPVOID arg);
void CALLBACK CompRoutine(DWORD, DWORD, LPWSAOVERLAPPED, DWORD);
int SendPacket(SOCKET hLisnSock, char * buffer, int bufferSz);
void DispatchMsg(DWORD Trans, LPWSAOVERLAPPED lpOverlapped);
void ProcessPacket();
bool ServerConnect(const SOCKET& sock, const SOCKADDR_IN& sockAdr);
bool InputID(const SOCKET& sock);
void QuitProgram(const SOCKET& sock);
void ShowChat();
void gotoxy(int x, int y)
{

	COORD pos = { x,y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

}
COORD getXY() {
	COORD Cur;
	CONSOLE_SCREEN_BUFFER_INFO a;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &a);
	Cur.X = a.dwCursorPosition.X;
	Cur.Y = a.dwCursorPosition.Y;
	return Cur;
}
void PushChat(const std::string& str);


int main()
{
	GlobalVal::gMutex = CreateMutex(nullptr, FALSE, nullptr);
	GlobalVal::Quit = FALSE;
	const u_short port = 12345;
	const char IPAddr[INET_ADDRSTRLEN] = "192.168.0.51";
	SOCKET hSock;
	SOCKADDR_IN sockAdr;
	WSADATA wsaData;

	WSAStartup(MAKEWORD(2, 2), &wsaData);
	ZeroMemory(&sockAdr, sizeof(sockAdr));

	hSock = socket(AF_INET, SOCK_STREAM, 0);

	sockAdr.sin_family = AF_INET;
	sockAdr.sin_port = htons(port);
	InetPtonA(AF_INET, IPAddr, &sockAdr.sin_addr);

	if (ServerConnect(hSock, sockAdr) == false)
	{
		QuitProgram(hSock);
		return 0;
	}

	if (InputID(hSock) == false)
	{
		QuitProgram(hSock);
		return 0;
	}

	WSAOVERLAPPED wsaOverlapped;
	WSABUF wsaBuf;
	wsaBuf.buf = GlobalVal::buf;
	wsaBuf.len = BUF_SZ;
	ZeroMemory(&wsaOverlapped, sizeof(WSAOVERLAPPED));
	wsaOverlapped.hEvent = &wsaBuf;

	HANDLE ThreadHandle = (HANDLE)_beginthreadex(NULL, 0, ThreadFunc, (LPVOID)hSock, 0, NULL);
	DWORD dwRet;
	do
	{
		SleepEx(100, TRUE);
		if (GetAsyncKeyState(VK_F11) & 0x8000)
		{
			system("cls");
		}
		DWORD recvBytes, flaginfo = 0;
		if (!GlobalVal::packetList.empty())
		{
			ProcessPacket();
		}
		int retval;
		retval = WSARecv(hSock, &wsaBuf, 1, &recvBytes, &flaginfo, &wsaOverlapped, CompRoutine);
		if (retval == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSA_IO_PENDING)
			{
				SrvUtil::ErrorMsg(_T("WsaRecv()"));
				GlobalVal::Quit = TRUE;
				continue;
			}
		}
	} while (GlobalVal::Quit != TRUE);

	dwRet = WaitForSingleObject(ThreadHandle, INFINITE);
	if (dwRet == WAIT_FAILED)
	{
		std::cout << "Thread Error" << std::endl;
		return -1;
	}

	QuitProgram(hSock);
	return 0;
}

UINT WINAPI ThreadFunc(LPVOID arg)
{
	static bool See = false;
	SOCKET hSock = (SOCKET)arg;
	do
	{
		if (See == false)
		{
			WaitForSingleObject(GlobalVal::gMutex, INFINITE);
			gotoxy(0, 25);
			std::cout << "\n                                                                                 \r";
			std::cout << "채팅 입력(Q 종료):";
			See = true;
			ReleaseMutex(GlobalVal::gMutex);
		}
		char chatbuf[BUF_SZ] = { 0, };
		if (_kbhit())
		{
			std::cin.getline(chatbuf, BUF_SZ);
			if (_stricmp(chatbuf, "q") == 0)
			{
				GlobalVal::Quit = TRUE;
				continue;
			}
			int retVal = SendPacket(hSock, chatbuf, (int)strlen(chatbuf) + 1);
			See = false;
		}
	} while (GlobalVal::Quit != TRUE);
	return 1;
}

void CALLBACK CompRoutine(DWORD dwError, DWORD dwByte, LPWSAOVERLAPPED lpOverlapped, DWORD flags)
{
	static int cnt = 0;
	if (cnt == 0 && (dwError != 0 || dwByte == 0))
	{
		++cnt;
		std::cout << "Server Disconnect" << std::endl;
		GlobalVal::Quit = TRUE;
		return;
	}
	HANDLE bufhandle = lpOverlapped->hEvent;
	LPWSABUF wsabuf = (LPWSABUF)bufhandle;

	DispatchMsg(dwByte, lpOverlapped);

	lpOverlapped->hEvent = nullptr;
	ZeroMemory(lpOverlapped, sizeof(WSAOVERLAPPED));
	lpOverlapped->hEvent = bufhandle;
}

void DispatchMsg(DWORD Trans, LPWSAOVERLAPPED lpOverlapped)
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

	LPWSABUF wsaBuf = ((LPWSABUF)lpOverlapped->hEvent);
	CopyMemory(&Buffer[WritePos], wsaBuf->buf, Trans);

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

			GlobalVal::packetList.push_back(addPacket);

			if (ReadPos < PACKET_HEADER_SIZE)
			{
				break;
			}

			Packet = (P_UPACKET)wsaBuf->buf;
		} while (ReadPos >= Packet->ph.len);
	}
}
void ProcessPacket()
{
	std::vector<UPACKET>::iterator iter;
	for (iter = GlobalVal::packetList.begin(); iter != GlobalVal::packetList.end(); ++iter)
	{
		UPACKET packet = ((UPACKET)*iter);

		switch (packet.ph.type)
		{
			case PACKET_CHAT_MSG:
			{
				PushChat(packet.msg);
			}break;
		}
	}
	GlobalVal::packetList.clear();
}
int SendPacket(SOCKET hLisnSock, char * buffer, int bufferSz)
{
	UPACKET packet;
	packet.ph.type = PACKET_CHAT_MSG;
	packet.ph.len = bufferSz + PACKET_HEADER_SIZE;
	CopyMemory(packet.msg, buffer, bufferSz);
	int Sendbyte;
	int TotalSendbyte = 0;
	char* SendMsg = (char*)&packet;
	do
	{
		Sendbyte = send(hLisnSock, &SendMsg[TotalSendbyte], packet.ph.len - TotalSendbyte, 0);
		if (Sendbyte == SOCKET_ERROR || Sendbyte == 0)
		{
			return Sendbyte;
		}
		TotalSendbyte += Sendbyte;
	} while (packet.ph.len > TotalSendbyte);
	return packet.ph.len;
}
bool ServerConnect(const SOCKET& sock, const SOCKADDR_IN& sockAdr)
{
	connect(sock, (SOCKADDR*)&sockAdr, sizeof(sockAdr));
	UPACKET packet;
	BOOL Ret = RecvPacket(sock, &packet);
	if (Ret == FALSE || packet.ph.type == PACKET_BANIP)
	{
		if (packet.ph.type == PACKET_BANIP)
		{
			CopyMemory(GlobalVal::BanMsg, packet.msg, packet.ph.len);
		}
		return false;
	}
	return true;
}
bool InputID(const SOCKET& sock)
{
	UPACKET packet;
	while (1)
	{
		BOOL Ret = RecvPacket(sock, &packet);
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
				SendPacket(sock, sendpacket);
			}break;
			case PACKET_CHAT_MSG:
			{
				system("cls");
				PushChat(packet.msg);
				return true;
			};
			default:
				break;
		}
	}
}
void QuitProgram(const SOCKET& sock)
{
	CloseHandle(GlobalVal::gMutex);
	closesocket(sock);
	WSACleanup();
	system("cls");
	std::cout << GlobalVal::BanMsg << std::endl;
	std::cout << "연결이 종료되었습니다. 아무키나 누르세요." << std::endl;
	_getch();
}
void ShowChat()
{
	WaitForSingleObject(GlobalVal::gMutex, INFINITE);
	COORD pos = getXY();
	gotoxy(0, 0);
	std::list<std::string>::iterator iter;
	for (iter = GlobalVal::ChatLog.begin(); iter != GlobalVal::ChatLog.end(); ++iter)
	{
		std::cout << "\t\t\t\t\t\t\t\t\t\t\r";
		std::cout << *iter << std::endl;
	}
	gotoxy(pos.X, pos.Y);
	ReleaseMutex(GlobalVal::gMutex);
}
void PushChat(const std::string& str)
{
	if (GlobalVal::ChatLog.size() >= 25)
	{
		GlobalVal::ChatLog.pop_back();
	}
	GlobalVal::ChatLog.push_front(str);
	ShowChat();
}