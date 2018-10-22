#include "stdafx.h"
#include "User.h"
#include "Synchronize.h"
#include "LogError.h"

void User::RecvData()
{
	DWORD Transfer, flags = 0;
	m_oV.m_iFlags = OVERLAPPED_EX::MODE_RECV;
	int iRet = WSARecv(m_Sock, &m_wsaBuffer, 1, &Transfer, &flags, (LPWSAOVERLAPPED)&m_oV, NULL);
	if (iRet == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
			I_LOG.T_ERROR();
		}
	}
}

User::User()
{
	m_wsaBuffer.buf = m_strBuffer;
	m_wsaBuffer.len = BUF_SIZE;
}
User::User(SOCKET Sock, SOCKADDR_IN Addr) : m_Sock(Sock), m_Addr(Addr)
{
	m_wsaBuffer.buf = m_strBuffer;
	m_wsaBuffer.len = BUF_SIZE;
}
User::User(const User& user) : m_Sock(user.m_Sock), m_Addr(user.m_Addr)
{
	m_wsaBuffer.buf = m_strBuffer;
	m_wsaBuffer.len = BUF_SIZE;
}
User::~User()
{
	m_wsaBuffer.buf = m_strBuffer;
	m_wsaBuffer.len = BUF_SIZE;
}

User* UserManager::getUser()
{
	User * pUser = new User;
	return pUser;
}
UserManager::UserManager()
{}

User* UserManager::AddUser(SOCKET clientSock, SOCKADDR_IN clientAddr)
{
	User* pUser = getUser();
	{
		Synchronize sync(this);
		pUser->m_Sock = clientSock;
		pUser->m_Addr = clientAddr;
		m_UserList.push_back(pUser);
	}
	return pUser;
}

bool UserManager::DelUser(SOCKET clientSock)
{
	{
		Synchronize sync(this);
		std::list<User*>::iterator iter;
		std::list<User*>::iterator Deliter = m_UserList.end();
		for (iter = m_UserList.begin(); iter != m_UserList.end();)
		{
			if ((*iter)->m_Sock == clientSock)
			{
				Deliter = iter;
				break;
			}
			else
			{
				++iter;
			}
		}
		if (Deliter != m_UserList.end())
		{
			closesocket((*iter)->m_Sock);
			m_UserList.erase(Deliter);
		}
	}
	return true;
}