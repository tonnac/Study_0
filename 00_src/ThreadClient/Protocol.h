#pragma once
#include <windows.h>
#define BUF_SZ 512

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
// PACKET_HEADER.type
#define PACKET_CHAT_MSG 1000
