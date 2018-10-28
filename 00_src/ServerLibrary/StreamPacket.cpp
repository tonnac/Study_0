#include "StreamPacket.h"
#include "Server.h"

StreamPacket::StreamPacket()
{
	ZeroMemory(mRecvBuf, MAX_BUF_SZ);
}
StreamPacket::~StreamPacket()
{}
void StreamPacket::Put(char* recvBuffer, int RecvSize, User* pUser)
{
	{
		Synchronize sync(this);

		if (mWritePos + RecvSize >= MAX_BUF_SZ)
		{
			char strTemp[MAX_BUF_SZ] = { 0, };
			CopyMemory(strTemp, &mRecvBuf[mStartPos], mReadPos);
			ZeroMemory(mRecvBuf, MAX_BUF_SZ);
			CopyMemory(mRecvBuf, strTemp, mReadPos);
			mStartPos = 0;
			mWritePos = mReadPos;
		}

		CopyMemory(&mRecvBuf[mWritePos], recvBuffer, RecvSize);
		mWritePos += RecvSize;
		mReadPos += RecvSize;

		if (mReadPos < PACKET_HEADER_SIZE) return;

		mPacket = (P_UPACKET)&mRecvBuf[mStartPos];

		if (mReadPos >= mPacket->ph.len)
		{
			do
			{
				TPACKET add;
				CopyMemory(&add.mPacket, &mRecvBuf[mStartPos], mPacket->ph.len);
				add.mUser = pUser;

				if (pUser != nullptr)
				{
					S_Server.AddPacket(add);
				}

				mReadPos -= mPacket->ph.len;
				mStartPos += mPacket->ph.len;

				if (mReadPos < PACKET_HEADER_SIZE)
				{
					break;
				}
				mPacket = (P_UPACKET)&mRecvBuf[mStartPos];

			} while (mReadPos >= mPacket->ph.len);
		}
	}
}
void StreamPacket::AddPacket(const TPACKET& pack)
{
	mPacketList.push_back(pack);
}
void StreamPacket::PacketClear()
{
	mPacketList.clear();
}
PACKET_ITER StreamPacket::PacketBegin()
{
	return mPacketList.begin();
}
PACKET_ITER StreamPacket::PacketEnd()
{
	return mPacketList.end();
}