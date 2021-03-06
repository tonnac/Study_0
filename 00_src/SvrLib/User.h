#pragma once
#include "StreamPacket.h"
#include "Thread.h"

typedef struct _OVERLAPPED_EX : public OVERLAPPED
{
	enum { MODE_RECV = 0, MODE_SEND = 1 };
	int m_iFlags;
} OVERLAPPED_EX, *LPOVERLAPPED_EX;

class User : public SvrObject
{
public:
	SOCKET			m_Sock;
	SOCKADDR_IN		m_Addr;
	WSABUF			m_wsaBuffer;
	char			m_strBuffer[BUF_SIZE];
	OVERLAPPED_EX	m_oV;
	StreamPacket	m_StreamPack;
public:
	void Dispatch(DWORD bytes, LPOVERLAPPED_EX ovex);
	void RecvData();
	void SendData();
public:
	User();
	User(SOCKET Sock, SOCKADDR_IN Addr);
	User(const User& user);
	virtual ~User();
};

class UserManager : public Singleton<UserManager>, public Thread
{
	friend class Singleton<UserManager>;
private:
	UserManager();
public:
	StreamPacket m_PacketList;
	void AddPacket(T_PACKET pack);
public:
	void Run() override;
	User* getUser();
	User* AddUser(SOCKET clientSock, SOCKADDR_IN clientAddr);
	bool DelUser(SOCKET clientSock);
public:
	std::list<User*> m_UserList;
};

#define I_User UserManager::getInst()