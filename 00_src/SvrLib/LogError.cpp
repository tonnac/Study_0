#include "stdafx.h"
#include "LogError.h"

void LogError::T_ERROR()
{
	if (WSAGetLastError() != WSA_IO_PENDING)
	{
		char* lpMsgBuf = NULL;
		FormatMessageA(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM, NULL,
			WSAGetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(char*)&lpMsgBuf, 0, NULL);
	//	if (bPrint)
	//	{
	//		MessageBoxA(NULL, lpMsgBuf, "ERROR", MB_OK);
	//	}
	//	else
	//	{
			OutputDebugStringA((char*)lpMsgBuf);
			printf("\n%s", (char*)lpMsgBuf);
	//	}
		LocalFree(lpMsgBuf);
	}
}

LogError::LogError()
{}
LogError::~LogError()
{}