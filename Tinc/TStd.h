#pragma once
#include "TCollision.h"
#include <assert.h>
#include <tchar.h>
#include <iostream>
#include <map>
#include <string>
#include <list>
#include <vector>
#include <tchar.h>
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"TCoreLib.lib")

using namespace std;
typedef std::basic_string<char> C_STR;
typedef std::basic_string<wchar_t> W_STR;
typedef std::basic_string<TCHAR> T_STR;


#define GAME_START int WINAPI WinMain(HINSTANCE hInst,	HINSTANCE hPrevInst,LPSTR   lpCmdLine,int   nCmdShow){
#define GAME_END }
#define GAME_RUN(s,w,h) GAME_START{ Sample win;win.SetWindow(hInst, L#s,w,h);win.Run();}GAME_END

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern float g_fSecPerFrame;
extern HDC g_hOffScreenDC;
extern HDC g_hScreenDC;
extern RECT  g_rtClient;
extern bool g_bActiveApp;
extern POINT g_pHeroPos;
template<class T> class TSingleton
{
public:
	static T& GetInstance()
	{
		static T theSingleInstance;
		return theSingleInstance;
	}
};
