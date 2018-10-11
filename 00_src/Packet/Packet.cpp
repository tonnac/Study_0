#include "Packet.h"

Packet::Packet(const WORD& type)
{
	ZeroMemory(&m_uPacket, sizeof(m_uPacket));
	m_uPacket.ph.type = type;
	m_pOffset = m_uPacket.msg;
}
Packet::Packet()
{
	ZeroMemory(&m_uPacket, sizeof(m_uPacket));
	m_pOffset = m_uPacket.msg;
}

void Packet::PutData(const char* pData, int iSize)
{
	m_uPacket.ph.len += iSize;
	memcpy(m_pOffset, pData, iSize);
	m_pOffset += iSize;
}
Packet& Packet::operator << (const char* data)
{
	int iSize = strlen(data) + 1;
	PutData(data, iSize);
	return *this;
}
Packet& Packet::operator << (const int& data)
{
	PutData((char*)&data, sizeof(data));
	return *this;
}
Packet& Packet::operator << (const std::string& data)
{
	PutData(data.c_str(), data.length());
	return *this;
}

void Packet::GetData(const char* pData, int iSize)
{
	memcpy(const_cast<char*>(pData), m_pOffset, iSize);
	m_pOffset += iSize;
}
Packet& Packet::operator >> (const char* data)
{
	int iSize = strlen(m_pOffset) + 1;
	GetData(const_cast<char*>(data), iSize);
	return *this;
}
Packet& Packet::operator >> (const int& data)
{
	GetData((char*)&data, sizeof(data));
	return *this;
}
Packet& Packet::operator >> (const std::string& data)
{
	int iSize = strlen(m_pOffset) + 1;
	char buffer[256] = { 0, };
	GetData(buffer, iSize);
	const_cast<std::string&>(data) = buffer;
	return *this;
}

UPACKET	Packet::getPacket() const
{
	return m_uPacket;
}