#include <windows.h>
#include <iostream>
#include <tchar.h>
#include <string>
#include <conio.h>

#define MAX_WORK_THREAD 4
#define MAX_READ_SIZE 4096

class Iocp
{
public:
	HANDLE		m_hIOCP;
	HANDLE		m_hFileRead;
	HANDLE		m_hFileWrite;
	HANDLE		m_hWorkThread[MAX_WORK_THREAD];
	HANDLE		m_hEventKillThread;
	char		m_szReadBuffer[MAX_READ_SIZE];
	OVERLAPPED	m_hReadOV;
	OVERLAPPED	m_hWriteOV;
	bool		m_bEnd;
public:
	void Init();
	void Frame();
	bool WaitForRead();
	bool DispatchRead(DWORD dwTransfer);
	bool DispatchWrite(DWORD dwTransfer);
	static DWORD WINAPI WorkerThread(LPVOID arg);
public:
	~Iocp() {}
	void Release()
	{
		CloseHandle(m_hFileRead);
		CloseHandle(m_hFileWrite);
		for (int i = 0; i < MAX_WORK_THREAD; ++i)
		{
			CloseHandle(m_hWorkThread[i]);
		}
		CloseHandle(m_hIOCP);
		CloseHandle(m_hEventKillThread);
	}
};

void Iocp::Init()
{
	m_bEnd = false;
	m_hEventKillThread = ::CreateEvent(NULL, TRUE, FALSE, L"KillThread");
	::ResetEvent(m_hEventKillThread);

	m_hFileRead = CreateFile(
	L"hhhg.zip", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 0);
	m_hFileWrite = CreateFile(
	L"copy.zip", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 0);

	DWORD id;
	for (int i = 0; i < MAX_WORK_THREAD; ++i)
	{
		m_hWorkThread[i] = ::CreateThread(NULL, 0, WorkerThread, this, 0, &id);
	}

	m_hIOCP = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);

	::CreateIoCompletionPort(m_hFileRead, m_hIOCP, (ULONG_PTR)m_hFileRead /*완료키*/, 0);
	::CreateIoCompletionPort(m_hFileWrite, m_hIOCP, (ULONG_PTR)m_hFileWrite, 0);
}
void Iocp::Frame()
{
	WaitForRead();
	while(WaitForMultipleObjects(MAX_WORK_THREAD, m_hWorkThread, TRUE, 1));
	Release();
}
bool Iocp::WaitForRead()
{
	DWORD dwReadBytes;
	if (::ReadFile(m_hFileRead, m_szReadBuffer, MAX_READ_SIZE, &dwReadBytes, &m_hReadOV) == FALSE)
	{
		if (GetLastError() == ERROR_IO_PENDING)
		{
			return true;
		}
		return false;
	}
	//else
	//{
	//	if (dwReadBytes == 0 || GetLastError() == ERROR_HANDLE_EOF)
	//	{
	//		return false;
	//	}
	//}
	return true;
}
bool Iocp::DispatchRead(DWORD dwTransfer)
{
	DWORD dwWritten;
	if (::WriteFile(m_hFileWrite, m_szReadBuffer, dwTransfer, &dwWritten, &m_hWriteOV) == FALSE)
	{
		if (GetLastError() != ERROR_IO_PENDING)
		{
			return false;
		}
	}

	LARGE_INTEGER data;
	data.QuadPart = dwTransfer;
	m_hReadOV.Offset += data.LowPart;
	m_hReadOV.OffsetHigh += data.HighPart;

	WaitForRead();
	return true;
}
bool Iocp::DispatchWrite(DWORD dwTransfer)
{
	LARGE_INTEGER data;
	data.QuadPart = dwTransfer;
	m_hWriteOV.Offset += data.LowPart;
	m_hWriteOV.OffsetHigh += data.HighPart;

	if (m_bEnd == true && dwTransfer < MAX_READ_SIZE)
	{
		::SetEvent(m_hEventKillThread);
	}
	return true;
}
DWORD WINAPI Iocp::WorkerThread(LPVOID arg)
{
	Iocp * iocp = (Iocp*)arg;
	OVERLAPPED ov;
	DWORD byteTransfer;
	ULONG_PTR keyValue;
	while (1)
	{
		if (WAIT_OBJECT_0 ==::WaitForSingleObject(iocp->m_hEventKillThread, 1))
		{
			break;
		}

		// IOCP QUEUE
		BOOL bRet = ::GetQueuedCompletionStatus(iocp->m_hIOCP, &byteTransfer, &keyValue, (LPOVERLAPPED*)&ov, 1);
		if (bRet == TRUE)
		{
			if (keyValue == (ULONG_PTR)iocp->m_hFileRead)
			{
				iocp->DispatchRead(byteTransfer);
			}
			else
			{
				iocp->DispatchWrite(byteTransfer);
			}
		}
		else
		{
			if (GetLastError() == WAIT_TIMEOUT)
			{
				continue;
			}
			if (GetLastError() == ERROR_HANDLE_EOF)
			{
				::SetEvent(iocp->m_hEventKillThread);
				continue;

			}
			// Error 부분
		}
	}
	return 0;
}
int main()
{
	Iocp iocp;
	iocp.Init();
	iocp.Frame();

	return 0;
}