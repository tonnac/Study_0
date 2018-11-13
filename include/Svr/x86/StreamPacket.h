#pragma once
#include "Synchronize.h"
#include "Protocol.h"

struct User;

typedef struct TPACKET
{
	TPACKET()
	{
		ZeroMemory(&mPacket, sizeof(mPacket));
	}
	UPACKET mPacket;
	User* mUser = nullptr;
}TPACKET, *LPTPACKET;

using PACKET_ITER = std::list<TPACKET>::iterator;

class StreamPacket : public ServerObj
{
public:
	StreamPacket();
	virtual ~StreamPacket();
public:
	void Put(char* recvBuffer, int RecvSize, User* pUser= nullptr);
	void AddPacket(const TPACKET& pack);
	void PacketClear();
	PACKET_ITER PacketBegin();
	PACKET_ITER PacketEnd();
private:
	std::list<TPACKET> mPacketList;
	P_UPACKET mPacket = nullptr;
	char	  mRecvBuf[MAX_BUF_SZ];
	DWORD	  mStartPos = 0;
	DWORD	  mWritePos = 0;
	DWORD	  mReadPos = 0;
};