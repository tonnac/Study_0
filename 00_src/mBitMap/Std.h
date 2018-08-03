#pragma once
#include <windows.h>
#include <tchar.h>
#include <string>
#include <map>
#include <list>

using C_STR = std::basic_string<char>;
using W_STR = std::basic_string<wchar_t>;
using T_STR = std::basic_string<TCHAR>;

#pragma comment(lib,"winmm.lib")

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

extern HWND			g_hWnd;				//타이머::렌더함수에서 사용
extern HINSTANCE	g_hInstance;		//비트맵::로드함수에서 사용
extern float		g_fSecPerFrame;
extern HDC			g_hOffScreenDC;