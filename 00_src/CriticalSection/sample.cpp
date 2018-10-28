#include <iostream>
#include <process.h>
#include <Windows.h>
#include <array>
#include <vector>

CRITICAL_SECTION cs1;

int num = 0;

UINT WINAPI ThreadFunc1(LPVOID arg);
UINT WINAPI ThreadFunc2(LPVOID arg);

int main()
{
	InitializeCriticalSection(&cs1);

	int k = 5;
	std::vector<HANDLE> handlearr;

	HANDLE handle = (HANDLE)_beginthreadex(nullptr, 0, ThreadFunc1, nullptr, 0, nullptr);
	handlearr.push_back(handle);
	handle = (HANDLE)_beginthreadex(nullptr, 0, ThreadFunc2, nullptr, 0, nullptr);
	handlearr.push_back(handle);


	WaitForMultipleObjects(2, handlearr.data(), TRUE, INFINITE);


	std::cout << num << std::endl;
	DeleteCriticalSection(&cs1);
	return 0;
}


UINT WINAPI ThreadFunc1(LPVOID arg)
{
	EnterCriticalSection(&cs1);
	for (int i = 0; i < 100000000; ++i)
	{
		num += 1;
	}
	LeaveCriticalSection(&cs1);
	return 1;
}
UINT WINAPI ThreadFunc2(LPVOID arg)
{
	EnterCriticalSection(&cs1);
	for (int i = 0; i < 500000000; ++i)
	{
		num -= 1;
	}
	LeaveCriticalSection(&cs1);
	return 1;
}