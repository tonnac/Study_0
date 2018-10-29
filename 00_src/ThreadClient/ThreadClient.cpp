#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <process.h>
#include <conio.h>
#include <vector>
#include "Protocol.h"

#pragma comment(lib, "ws2_32")


namespace GlobalVal
{
	std::vector<UPACKET> packetList;
	BOOL Quit;
	char buf[BUF_SZ];
}

UINT WINAPI ThreadFunc(LPVOID arg);
void CALLBACK CompRoutine(DWORD, DWORD, LPWSAOVERLAPPED, DWORD);
int SendPacket(SOCKET hLisnSock, char * buffer, int bufferSz);
void DispatchMsg(DWORD Trans, LPWSAOVERLAPPED lpOverlapped);
void ProcessPacket();

int main()
{
	GlobalVal::Quit = FALSE;
	const u_short port = 12347;
	const char IPAddr[INET_ADDRSTRLEN] = "219.254.48.7";
	SOCKET hSock;
	SOCKADDR_IN sockAdr;
	WSADATA wsaData;

	WSAStartup(MAKEWORD(2, 2), &wsaData);
	ZeroMemory(&sockAdr, sizeof(sockAdr));

	hSock = socket(AF_INET, SOCK_STREAM, 0);

	sockAdr.sin_family = AF_INET;
	sockAdr.sin_port = htons(port);
	InetPtonA(AF_INET, IPAddr, &sockAdr.sin_addr);

	WSAOVERLAPPED wsaOverlapped;
	WSABUF wsaBuf;
	wsaBuf.buf = GlobalVal::buf;
	wsaBuf.len = BUF_SZ;
	ZeroMemory(&wsaOverlapped, sizeof(WSAOVERLAPPED));
	wsaOverlapped.hEvent = &wsaBuf;
	connect(hSock, (SOCKADDR*)&sockAdr, sizeof(sockAdr));
	HANDLE ThreadHandle = (HANDLE)_beginthreadex(NULL, 0, ThreadFunc, (LPVOID)hSock, 0, NULL);
	DWORD dwRet;
	do
	{
		SleepEx(100, TRUE);
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


	return 0;
}

UINT WINAPI ThreadFunc(LPVOID arg)
{
	SOCKET hSock = (SOCKET)arg;
	do
	{
		char chatbuf[BUF_SZ];
		if (_kbhit())
		{
			fgets(chatbuf, BUF_SZ, stdin);
			if (_stricmp(chatbuf, "q\n") == 0)
			{
				GlobalVal::Quit = TRUE;
				continue;
			}
			int retVal = SendPacket(hSock, chatbuf, (int)strlen(chatbuf) + 1);
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
				std::cout << packet.msg << std::endl;
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