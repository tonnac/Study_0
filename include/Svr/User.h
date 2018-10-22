#pragma once
#include "SvrStd.h"
#include "SvrObject.h"

class User
{
public:
	SOCKET m_Sock;
	SOCKADDR_IN m_Addr;
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
	bool AddUser(SOCKET clientSock, SOCKADDR_IN clientAddr);
	bool DelUser(SOCKET clientSock);
public:
	std::list<User*> m_UserList;
};

#define I_User UserManager::getInst()