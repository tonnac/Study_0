#pragma once
#include "SrvUtil.h"

#pragma pack(push, 1)
typedef struct
{
	WORD len;
	WORD type;
} PACKET_HEADER;

typedef struct
{
	PACKET_HEADER ph;
	char msg[BUF_SZ];
}UPACKET, *P_UPACKET;

#pragma pack(pop)

#define PACKET_HEADER_SIZE 4
// PACKET_HEADER.type
#define PACKET_CHAT_MSG 1000