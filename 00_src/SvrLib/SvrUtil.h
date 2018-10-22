#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <process.h>
#include <Windows.h>

#pragma comment(lib, "SvrLib")
#pragma comment(lib, "ws2_32")

#ifndef ExptSocketError
#define ExptSocketError(x)			\
{									\
	int iRet = (x);					\
	if (iRet == SOCKET_ERROR)		\
	{								\
		return false;				\
	}								\
}
#endif