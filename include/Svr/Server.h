#pragma once
#include "Acceptor.h"
#include "ServerModel.h"
#include "StreamPacket.h"

enum class IOState : unsigned char
{
	RECV = 0,
	SEND
};

typedef struct OVERLAPPEDEX
{
	OVERLAPPED mOverlapped;
	IOState mioState;
} OVERLAPPEDEX, *LPOVERLAPPEDEX;

struct User
{
	User()
	{
		ZeroMemory(&mOverlappedex, sizeof(mOverlappedex));
		ZeroMemory(&mUserAdr, sizeof(mUserAdr));
		mWsaBuf.buf = mBuf;
		mWsaBuf.len = BUF_SZ;
		mOverlappedex.mioState = IOState::RECV;
	}
	void Dispatch(DWORD Trans, LPOVERLAPPEDEX lpoverlapped)
	{
		if (Trans == 0) return;

		if (lpoverlapped->mioState == IOState::RECV)
		{
			mStreamPacket.Put(mWsaBuf.buf, Trans, this);
		}
		WaitForpacketReceive();
	}
	void WaitForpacketReceive()
	{
		int iRet = 0;
		DWORD cbTransferred, flags = 0;
		mOverlappedex.mioState = IOState::RECV;
		mWsaBuf.buf = mBuf;
		mWsaBuf.len = BUF_SZ;
		iRet = WSARecv(mUserSock, &mWsaBuf, 1, &cbTransferred, &flags, &mOverlappedex.mOverlapped, nullptr);
		if (iRet == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSA_IO_PENDING)
			{
				SrvUtil::ErrorMsg(_T("WaitForpacketReceive"));
			}
		}
	}
	OVERLAPPEDEX		mOverlappedex;
	SOCKET				mUserSock;
	SOCKADDR_IN			mUserAdr;
	WSABUF				mWsaBuf;
	StreamPacket		mStreamPacket;
	std::string			mUserID;
	char				mBuf[BUF_SZ];
};


using UserPtr = std::shared_ptr<User>;
using UserIter = std::list<UserPtr>::const_iterator;

struct UserPred
{
	User* user;
	UserPred(User* puser) : user(puser)
	{}
	bool operator() (UserPtr rhs)
	{
		if (user->mUserSock == rhs->mUserSock)
		{
			return true;
		}
		return false;
	}
};


class Server : public ServerObj
{
private:
	Server();
public:
	static Server& getInstance()
	{
		static Server ins;
		return ins;
	}
	virtual ~Server();
public:
	void							Initialize();
	void							Run();
	void							AddUser(const SOCKET& clntSock, const SOCKADDR_IN clntAdr);
	void							RemoveUser(User* user);
	void							ProcessPacket();
	void							AddPacket(const TPACKET& pack);
	int								SendPacket(User* pUser, const UPACKET& packetMsg);
private:
	StreamPacket					mStreamPacket;
	HANDLE							mMutex;
	std::list<UserPtr>				mUserList;
	std::shared_ptr<ServerModel>	mServerModel;
	Acceptor						mAcceptor;
};

#define S_Server Server::getInstance()