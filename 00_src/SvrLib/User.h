#pragma once
#include "SvrStd.h"
#include "SvrObject.h"

typedef struct _OVERLAPPED_EX : public OVERLAPPED
{
	enum { MODE_RECV = 0, MODE_SEND = 1 };
	int m_iFlags;
} OVERLAPPED_EX, *LPOVERLAPPED_EX;

class User
{
public:
	SOCKET			m_Sock;
	SOCKADDR_IN		m_Addr;
	WSABUF			m_wsaBuffer;
	char			m_strBuffer[BUF_SIZE];
	OVERLAPPED_EX	m_oV;
public:
	void RecvData();
public:
	User();
	User(SOCKET Sock, SOCKADDR_IN Addr);
	User(const User& user);
	virtual ~User();
};

class UserManager : public Singleton<UserManager>, public SvrObject
{
	friend class Singleton<UserManager>;
private:
	UserManager();
public:
	User* getUser();
	User* AddUser(SOCKET clientSock, SOCKADDR_IN clientAddr);
	bool DelUser(SOCKET clientSock);
public:
	std::list<User*> m_UserList;
};

#define I_User UserManager::getInst()