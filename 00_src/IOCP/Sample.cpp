#include <windows.h>
#include <iostream>
#include <tchar.h>
#include <memory>
#include <string>

OVERLAPPED ov;
LARGE_INTEGER g_size;
char * buf = NULL;

using Char_Ptr = std::shared_ptr<char>;
using wChar_Ptr = std::shared_ptr<wchar_t>;

Char_Ptr GetW2M(const wchar_t* data)
{
	char cData[1024] = { 0, };
	int iLength = WideCharToMultiByte(CP_ACP, 0, data, -1, 0, 0, NULL, NULL);
	int iRet = WideCharToMultiByte(CP_ACP, 0, data, -1, cData, iLength, NULL, NULL);
	Char_Ptr lData = std::make_shared<char>(iLength);
	char * pData = NULL;
	pData = lData.get();
	CopyMemory(pData, cData, iLength);
	return lData;
}
wChar_Ptr GetM2W(const char* data)
{
	wchar_t cData[1024] = { 0, };
	int iLength = MultiByteToWideChar(CP_ACP, 0, data, -1, 0, 0);
	int iRet = MultiByteToWideChar(CP_ACP, 0, data, -1, cData, iLength);
	wChar_Ptr lData = std::make_shared<wchar_t>(iLength);
	wchar_t * pData = NULL;
	pData = lData.get();
	CopyMemory(pData, cData, iLength);
	return lData;
}
std::string w2m(std::wstring& data)
{
	std::string ret = std::string(data.begin(), data.end());
	return ret;
}
std::wstring m2w(std::string& data)
{
	std::wstring ret = std::wstring(data.begin(), data.end());
	return ret;
}

void FileRead(HANDLE hReadFile, DWORD offset)
{
	DWORD dwLength = 4096; //filesize.QuadPart;
	g_size.QuadPart += offset;

	ov.Offset = g_size.LowPart;
	ov.OffsetHigh = g_size.HighPart;

	char* pTemp = &buf[g_size.QuadPart];
	DWORD dwRead;
	BOOL iRet = ReadFile(hReadFile, pTemp, dwLength, &dwRead, &ov);

	if (iRet == FALSE)
	{
		if (GetLastError() == ERROR_IO_PENDING)
		{
			printf("\nREAD.........");
		}
	}
}

int main(void)
{
	LARGE_INTEGER Frequency;
	LARGE_INTEGER Frequency1;
	LARGE_INTEGER Frequency2;
	DWORD dwLength = 0;
	QueryPerformanceFrequency(&Frequency);
	
	LARGE_INTEGER filesize;
	HANDLE hReadfile = CreateFileA(
		"Map.png",
		GENERIC_READ, 0, NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
		NULL
	);


	if (hReadfile != INVALID_HANDLE_VALUE)
	{
		GetFileSizeEx(hReadfile, &filesize);
		buf = new char[filesize.QuadPart];

		if (buf == NULL)
		{
			return -1;
		}

		QueryPerformanceCounter(&Frequency1);
		FileRead(hReadfile, 0);

		while (1)
		{
			DWORD trans = 0;
			BOOL ret = GetOverlappedResult(
				hReadfile, &ov, &trans, TRUE);
			if (ret == TRUE)
			{
				if (filesize.QuadPart <= g_size.QuadPart)
				{
					QueryPerformanceCounter(&Frequency2);
					printf("\n%4.3fSec\n", (Frequency2.LowPart - Frequency1.LowPart) / (float)Frequency.LowPart);
					break;
				}
				FileRead(hReadfile, trans);
			}
			else
			{
				printf("\nREAD.........byte:%d",g_size.LowPart);
			}
		}

		//if (iRet == TRUE)
		//{
		//	//std::wstring strWData = buf;
		//	//std::string strCData;
		//	//printf("%s\n", strCData.c_str());
		//	//wprintf_s(L"%s\n", GetM2W(GetW2M(buf).get()).get());
		//	//wprintf_s(L"%s", buf);
		//	//_tcprintf(L"%s", buf);
		//}
	}

	CloseHandle(hReadfile);

	OVERLAPPED wOv;
	ZeroMemory(&wOv, sizeof(OVERLAPPED));

	HANDLE hWritefile = CreateFileA(
		"qqq.zip",
		GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
		NULL
	);

	if (hWritefile != INVALID_HANDLE_VALUE)
	{
		DWORD dwWritten = 0;
		BOOL iRet = WriteFile(hWritefile, buf, filesize.QuadPart, &dwWritten, &wOv);
		QueryPerformanceCounter(&Frequency1);
		if (iRet == FALSE)
		{
			if (GetLastError() == ERROR_IO_PENDING)
			{
				printf("\nWrite.....");
			}
		}

		while (1)
		{
			DWORD trans = 0;
			BOOL ret = GetOverlappedResult(
				hReadfile, &wOv, &trans, TRUE);
			if (ret == TRUE)
			{
				QueryPerformanceCounter(&Frequency2);
				printf("\nfinish time %4f.", (Frequency2.LowPart - Frequency1.LowPart) / (float)Frequency.LowPart);
				break;
			}
			else
			{
				printf("\nWRITE.........");
			}
		}
	}
	CloseHandle(hWritefile);
	delete[] buf;

	return 0;
}