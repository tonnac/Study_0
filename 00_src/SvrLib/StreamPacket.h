#pragma once
#include "SvrStd.h"
#include "Protocol.h"
#define MAX_RECV_SIZE 2048 * 2

class User;

typedef struct
{
	UPACKET packet;
	User* pUser;
} T_PACKET, *LPT_PACKET;

class StreamPacket
{
public:
	std::list<T_PACKET> m_packetList;
	DWORD				m_dwWritePos;
	DWORD				m_dwReadPos;
	DWORD				m_dwStartPos;
	LPUPACKET			m_pPacket;
	char				m_recvBuffer[MAX_RECV_SIZE];
public:
	void Put(char* buf, int iRet, User * pUser);
public:
	StreamPacket();
	virtual ~StreamPacket();
};