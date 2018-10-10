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
	INT iData[20];
}CHARACTER_INFO;

#pragma pack(pop)

#define PACKET_HEADER_SIZE 4
// PACKET_HEADER.type
#define PACKET_CHAT_MSG 1000
#define PACKET_CREATE_CHARACTER 2000


// SEND
//UPACKET packet;
//ZeroMemory(&packet, sizeof(packet));
//
//char buffer[] = "KGCA";
//packet.ph.len = PACKET_HEADER_SIZE + strlen(buffer);
//packet.ph.type = PACKET_CHAT_MSG;
//memcpy(packet.msg, buffer, strlen(buffer));
//send(sock, (char*)&packet, packet.ph.len, 0);

//CHARACTER_INFO cinfo;
//ZeroMemory(&cinfo, sizeof(cinfo));
//cinfo.szName = ;
//cinfo.iIndex = ;
//cinfo.iData = ;
//packet.ph.len = PACKET_HEADER_SIZE + sizeof(cinfo);
//packet.ph.type = PACKET_CHAT_MSG;
//memcpy(packet.msg, (char*)cinfo, sizeof(cinfo));
//send(sock, (char*)&packet, packet.ph.len, 0);

// RECV
//char buffer[BUF_SIZE] = { 0, };
//int iRecvByte = 0;
//while (true)
//{
//	iRecvByte += recv(sock, buffer[iRecvByte], sizeof(char) * PACKET_HEADER_SIZE - iRecvByte, 0);
//	if (iRecvByte == PACKET_HEADER_SIZE)
//	{
//		UPACKET packet;
//		ZeroMemory(&packet, sizeof(packet));
//		memcpy(packet.ph.len, buffer, sizeof(char) * PACKET_HEADER_SIZE);
//		int rByte = 0;
//		do
//		{
//			rByte += recv(sock, packet.msg[rByte], sizeof(char) * packet.ph.len - rByte, 0);
//		} while (packet.ph.len > rByte);
//
//		iRecvByte = 0;
//		switch (packet.ph.type)
//		{
//			case PACKET_CHAT_MSG:
//			{
//				printf("패킷완성%s", packet.msg);
//			}break;
//			case PACKET_CREATE_CHARACTER:
//			{
//				CHARACTER_INFO charinfo;
//				memcpy(charinfo, packet.msg, sizeof(charinfo));
//			}break;
//		default:
//			break;
//		}
//		printf("패킷완성 %s", packet.msg);
//	}
//}