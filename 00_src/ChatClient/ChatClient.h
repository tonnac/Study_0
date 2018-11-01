#pragma once
#include "Protocol.h"
#include "SrvUtil.h"

class ChatClient
{
public:
	ChatClient();
public:
	bool Initialize();
	void Run();
private:
	bool InputID();
	void InputIPAndPort();
	void ProcessPacket();
	void ShowChat();
	void PushChat(const std::string& str);
	void QuitProgram();
	void DispatchMsg(DWORD Trans, LPWSAOVERLAPPED lpOverlapped);
private:
	static void gotoxy(int x, int y);
	static COORD getXY();
private:
	static UINT WINAPI ConnectFunc(LPVOID arg);
	static UINT WINAPI ThreadFunc(LPVOID arg);
	static UINT WINAPI ShowChat(LPVOID arg);
	static void CALLBACK CompRoutine(DWORD, DWORD, LPWSAOVERLAPPED, DWORD);
private:
	std::vector<UPACKET> mPacketList;
	BOOL mQuit;
	WSABUF mWsaBuf;
	char mbuf[BUF_SZ];
	char mBanMsg[BUF_SZ];
	WSAOVERLAPPED mWsaOverlapped;
	std::list<std::string> mChatLog;
	HANDLE mMutex;
	HANDLE mEvent;
	SOCKET mhSock;
	SOCKADDR_IN msockAdr;
};