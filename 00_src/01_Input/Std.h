#pragma once
#include <windows.h>
#include <tchar.h>

#pragma comment(lib,"winmm.lib")


extern HWND g_hWnd;

template <class K>
class Singleton
{
protected:
	Singleton() {}
public:
	static K& getInstance()
	{
		static K inst;
		return inst;
	}
};