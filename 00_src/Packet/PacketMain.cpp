#include <WinSock2.h>		//winsock2�� windows.h ���� ���� �־���Ѵ�.
#include "Packet.h"

#pragma comment(lib,"ws2_32.lib")

int SendMsg(SOCKET sock, const char* msg, WORD type);

int main(void)
{
	SOCKET sock;
	ZeroMemory(&sock, sizeof(sock));
	SendMsg(sock, "game", PACKET_CHAT_MSG);

	return 0;
}

int SendMsg(SOCKET sock, const char* msg, WORD type)
{
	std::string address = "�����";
	Packet sendPacket(type);
	sendPacket << msg << 1000 << address;
	UPACKET upacket = sendPacket.getPacket();
	int iByte = send(sock, (char*)&sendPacket, upacket.ph.len + PACKET_HEADER_SIZE, 0);

	char name[5] = { 0, };
	int iValue = 0;
	std::string e;

	Packet recvPacket;
	recvPacket.m_uPacket.ph = sendPacket.m_uPacket.ph;
	memcpy(recvPacket.m_uPacket.msg, sendPacket.m_uPacket.msg, sizeof(char) * 256);

	recvPacket >> name;
	recvPacket >> iValue;
	recvPacket >> e;

	return iByte;
}