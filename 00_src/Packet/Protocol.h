#pragma once
#include <windows.h>
#define BUF_SIZE 256

#pragma pack(push, 1)
typedef struct
{
	WORD len;
	WORD type;
} PACKET_HEADER;

typedef struct
{
	PACKET_HEADER ph;
	char msg[BUF_SIZE];
}UPACKET, *P_UPACKET;

typedef struct
{
	BYTE szName[13];
	INT iIndex;
}CHARACTER_INFO;
#pragma pack(pop)

#define PACKET_HEADER_SIZE 4
// PACKET_HEADER.type
#define PACKET_CHAT_MSG 1000
#define PACKET_CREATE_CHARACTER 2000
