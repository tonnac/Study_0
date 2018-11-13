#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <process.h>
#include <Windows.h>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <memory>
#include <cstdint>
#include <iostream>
#include <tchar.h>
#include <algorithm>
#include <ctime>
#include <string>
#include <cstring>
#include <conio.h>
#include <queue>

#pragma comment(lib, "DBServerLibrary")
#pragma comment(lib, "ws2_32")

#define BUF_SZ 2048
#define MAX_BUF_SZ 10000

namespace std
{
	using tstring = std::basic_string<TCHAR>;
}

class SrvUtil
{
public:

	static std::wstring MtoWString(const std::string& str)
	{
		return std::wstring(str.begin(), str.end());
	}

	static std::string WtoMString(const std::wstring& str)
	{
		return std::string(str.begin(), str.end());
	}

	static std::string WtoMChar(const wchar_t* src)
	{
		std::string strRet;
		int iLength = WideCharToMultiByte(CP_ACP, 0, src, -1, 0, 0, nullptr, nullptr);
		int iRet = WideCharToMultiByte(CP_ACP, 0, src, -1, const_cast<char*>(strRet.c_str()), iLength, nullptr, nullptr);
		return strRet;
	}

	static std::wstring MtoWChar(const char* src)
	{
		std::wstring strRet;
		int iLength = MultiByteToWideChar(CP_ACP, 0, src, -1, nullptr, 0);
		int iRet = MultiByteToWideChar(CP_ACP, 0, src, -1, const_cast<wchar_t*>(strRet.c_str()), iLength);
		return strRet;
	}

	static void ErrorMsg(const TCHAR* msg)
	{
		LPVOID lpMsgBuf;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (TCHAR*)&lpMsgBuf, 0, nullptr);
		MessageBox(nullptr, (TCHAR*)lpMsgBuf, msg, MB_ICONERROR);
		LocalFree(lpMsgBuf);
	}

	static std::vector<std::string> mThreadName;

	static CRITICAL_SECTION mCs;

};

template <typename X>
class Singleton
{
protected:
	Singleton();
public:
	static X& getInstance()
	{
		static X inst;
		return inst;
	}
};

extern bool isExit;