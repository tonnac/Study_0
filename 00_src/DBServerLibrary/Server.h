#pragma once
#include "Acceptor.h"
#include "ServerModel.h"
#include "StreamPacket.h"
#include "SQLServer.h"

#define ADD_TIME 0x0001
#define ADD_ID 0x0010

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
	User() : misActive(false)
	{
		ZeroMemory(&mOverlappedex, sizeof(mOverlappedex));
		ZeroMemory(&mUserAdr, sizeof(mUserAdr));
		mWsaBuf.buf = mBuf;
		mWsaBuf.len = BUF_SZ;
		mOverlappedex.mioState = IOState::RECV;
	}
	User(SOCKET sock, const SOCKADDR_IN& useradr) : mUserSock(sock), mUserAdr(useradr), misActive(false)
	{
		ZeroMemory(&mOverlappedex, sizeof(mOverlappedex));
		mWsaBuf.buf = mBuf;
		mWsaBuf.len = BUF_SZ;
		mOverlappedex.mioState = IOState::RECV;
	}
	~User()
	{
		closesocket(mUserSock);
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
	bool				misActive;
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
protected:
	Server();
public:
	static Server* getInstance()
	{
		return mServer;
	}
	virtual ~Server();

public:
	bool							Initialize();
	void							ServerRun();
	virtual void					Run();

	void							AddInfo(User * pUser, P_UPACKET pPacket, DWORD flag);
	void							AddUser(const SOCKET& clntSock, const SOCKADDR_IN clntAdr);
	void							EditID(const std::string& befUserID, const std::string& aftUserID);
	void							RemoveUser(User* user);

	void							ProcessPacket();
	void							AddPacket(TPACKET& pack);
	int								SendPacket(User* pUser, const UPACKET& packetMsg);

	bool							CheckUser(const std::string& IPaddr);

protected:
	virtual u_short					PortSet();
	static UINT WINAPI				ConnectDB(LPVOID arg);
protected:
	SQLServer						mSql;
	static Server*					mServer;
	StreamPacket					mStreamPacket;
	HANDLE							mMutex;
	std::vector<std::string>		mBanIP;
	std::list<UserPtr>				mUserList;
	std::unique_ptr<ServerModel>	mServerModel;
	Acceptor						mAcceptor;
};

#define S_Server Server::getInstance()