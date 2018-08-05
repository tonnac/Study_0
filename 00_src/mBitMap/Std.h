#pragma once
#include <windows.h>
#include <assert.h>
#include <tchar.h>
#include <string>
#include <map>
#include <list>

using T_STR = std::basic_string<TCHAR>;

#pragma comment(lib,"winmm.lib")


template <class K>
class Singleton
{
protected:
	Singleton() {}
public:
	static K & getInstance()
	{
		static K inst;
		return inst;
	}
};


extern HWND					g_hWnd;					//  Timer::Render()
extern HINSTANCE			g_hInstance;			//	Bitmap::LoadFile()
extern HDC					g_hOffScreenDC;			//  Render()
extern float				g_fSecPerFrame;			//  Sample::Frame()