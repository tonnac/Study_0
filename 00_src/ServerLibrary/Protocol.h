#pragma once
#include "SrvUtil.h"

#pragma pack(push, 1)
typedef struct PACKET_HEADER
{
	PACKET_HEADER() : len(0), type(0)
	{}
	WORD len;
	WORD type;
} PACKET_HEADER;

typedef struct UPACKET
{
	UPACKET()
	{
		ZeroMemory(msg, BUF_SZ);
	}
	PACKET_HEADER ph;
	char msg[BUF_SZ];
}UPACKET, *P_UPACKET;
#pragma pack(pop)

#define PACKET_HEADER_SIZE 4
#define PACKET_CHAT_MSG 1000
#define PACKET_CHAT_NAME_ACK 1001

#ifndef PACKET
#define PACKET
namespace Packet
{
	static BOOL SendPacket(const SOCKET& sock, const UPACKET& packet)
	{
		int TotalSendByte = 0;
		do
		{
			int SendByte = send(sock, (char*)&packet, packet.ph.len, 0);
			if (SendByte == SOCKET_ERROR || SendByte == 0)
			{
				SrvUtil::ErrorMsg(_T("AcceptThread()"));
				return FALSE;
			}
			TotalSendByte += SendByte;
		} while (TotalSendByte < packet.ph.len);
		return TRUE;
	}
};
#endif