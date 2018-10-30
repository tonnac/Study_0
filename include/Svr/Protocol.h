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
	UPACKET& operator = (const UPACKET& rhs)
	{
		CopyMemory(this, &rhs, sizeof(UPACKET));
		return *this;
	}
	PACKET_HEADER ph;
	char msg[BUF_SZ];
}UPACKET, *P_UPACKET;
#pragma pack(pop)

#define PACKET_HEADER_SIZE 4
#define PACKET_CHAT_MSG 1000
#define PACKET_CHAT_NAME_REQ 1001
#define PACKET_CHAT_NAME_ACK 1002
#define PACKET_BANIP 1003
#define PACKET_QUIT_ACK 1004
#define PACKET_PERMISSION 1005
#define PACKET_ENTER 1006
#define PACKET_LEAVE 1007

namespace PacketUtil
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

	static BOOL RecvPacket(const SOCKET& sock, UPACKET* packet)
	{
		int recvByte, TotalRecvByte = 0;
		char buf[BUF_SZ];
		do
		{
			recvByte = recv(sock, &buf[TotalRecvByte], PACKET_HEADER_SIZE - TotalRecvByte, 0);
			if (recvByte == 0 || recvByte == SOCKET_ERROR)
			{
				return FALSE;
			}
			TotalRecvByte += recvByte;
		} while (TotalRecvByte < PACKET_HEADER_SIZE);
		CopyMemory(&packet->ph, buf, PACKET_HEADER_SIZE);
		TotalRecvByte = 0;
		do
		{
			recvByte = recv(sock, &buf[TotalRecvByte], packet->ph.len - TotalRecvByte, 0);
			if (recvByte == 0 || recvByte == SOCKET_ERROR)
			{
				return FALSE;
			}
			TotalRecvByte += recvByte;
		} while (TotalRecvByte < packet->ph.len - PACKET_HEADER_SIZE);
		CopyMemory(packet->msg, buf, packet->ph.len - PACKET_HEADER_SIZE);
		return TRUE;
	}

	static int SendPacket(SOCKET hLisnSock, char * buffer, int bufferSz)
	{
		UPACKET packet;
		packet.ph.type = PACKET_CHAT_MSG;
		packet.ph.len = bufferSz + PACKET_HEADER_SIZE;
		CopyMemory(packet.msg, buffer, bufferSz);
		int Sendbyte;
		int TotalSendbyte = 0;
		char* SendMsg = (char*)&packet;
		do
		{
			Sendbyte = send(hLisnSock, &SendMsg[TotalSendbyte], packet.ph.len - TotalSendbyte, 0);
			if (Sendbyte == SOCKET_ERROR || Sendbyte == 0)
			{
				return Sendbyte;
			}
			TotalSendbyte += Sendbyte;
		} while (packet.ph.len > TotalSendbyte);
		return packet.ph.len;
	}

	class Packet
	{
	public:
		Packet();
		Packet(const WORD& type);
		~Packet() = default;
	public:
		Packet& operator << (const char* data);
		Packet& operator << (const int& data);
		Packet& operator << (const std::string& data);
	public:
		Packet& operator >> (const char* data);
		Packet& operator >> (const int& data);
		Packet& operator >> (const std::string& data);
	public:
		UPACKET	getPacket() const;
	private:
		void	GetData(const char* pData, int iSize);
		void	PutData(const char* pData, int iSize);
	private:
		UPACKET	m_uPacket;
		char *	m_pOffset;
	};
};