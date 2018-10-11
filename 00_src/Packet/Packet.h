#pragma once
#include "Protocol.h"
#include <string>
#include <iostream>

class Packet
{
public:
	Packet();
	Packet(const WORD& type);
	~Packet() = default;
public:
	void	PutData		(const char* pData, int iSize);
	Packet& operator << (const char* data);
	Packet& operator << (const int& data);
	Packet& operator << (const std::string& data);
public:
	void	GetData		(const char* pData, int iSize);
	Packet& operator >> (const char* data);
	Packet& operator >> (const int& data);
	Packet& operator >> (const std::string& data);
public:
	UPACKET	getPacket() const;
public:
	UPACKET	m_uPacket;
	char *	m_pOffset;
};