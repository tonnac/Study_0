#include "stdafx.h"
#include "StreamPacket.h"
#include "User.h"

void StreamPacket::Put(char* buf, int iRet, User * pUser)
{
	if (m_dwWritePos + iRet >= MAX_RECV_SIZE)
	{
		char strTemp[MAX_RECV_SIZE] = { 0, };
		memcpy(strTemp, &m_recvBuffer[m_dwStartPos], m_dwReadPos);
		ZeroMemory(&m_recvBuffer, sizeof(char)* MAX_RECV_SIZE);
		memcpy(&m_recvBuffer, &strTemp, m_dwReadPos);
		m_pPacket = (LPUPACKET)m_recvBuffer;
		m_dwStartPos = 0;
		m_dwWritePos = m_dwReadPos;
	}
	memcpy(&m_recvBuffer[m_dwWritePos], buf, iRet);
	m_dwWritePos += iRet;
	m_dwReadPos += iRet;

	if (m_dwReadPos <= PACKET_HEADER_SIZE)
	{
		return;
	}

	m_pPacket = (LPUPACKET)&m_recvBuffer[m_dwStartPos];
	if (m_dwReadPos >= m_pPacket->ph.len + PACKET_HEADER_SIZE)
	{
		do
		{
			T_PACKET addpacket;
			addpacket.pUser = pUser;
			memcpy(&addpacket.packet, &m_recvBuffer[m_dwStartPos], m_pPacket->ph.len + PACKET_HEADER_SIZE);
			I_User.AddPacket(addpacket);

			m_dwReadPos -= m_pPacket->ph.len + PACKET_HEADER_SIZE;
			m_dwStartPos += m_pPacket->ph.len + PACKET_HEADER_SIZE;

			if (m_dwReadPos < PACKET_HEADER_SIZE) break;

			m_pPacket = (LPUPACKET)&m_recvBuffer[m_dwStartPos];
		} while (m_dwReadPos >= m_pPacket->ph.len + PACKET_HEADER_SIZE);
	}
}

StreamPacket::StreamPacket() : m_dwReadPos(0), m_dwWritePos(0), m_dwStartPos(0)
{
}
StreamPacket::~StreamPacket()
{

}