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
#pragma comment(lib,"TCorelib.lib")

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

struct TIndex
{
	int x, y;
	bool operator == (const TIndex& pos)
	{
		return (x == pos.x && y == pos.y);
	}
	TIndex(int fX, int fY)
	{
		x = fX;
		y = fY;
	}
	TIndex()
	{
		x = y = 0.0f;
	}
};

template<class T> class TSingleton
{
public:
	static T& GetInstance()
	{
		static T theSingleInstance;
		return theSingleInstance;
	}
};

struct Nodeindex
{
	Nodeindex operator*(const int& Multipie)
	{
		Nodeindex rn = *this;
		rn._x *= Multipie;
		rn._y *= Multipie;
		return rn;
	}
	Nodeindex& operator*=(const int& Multipie)
	{
		this->_x *= Multipie;
		this->_y *= Multipie;
		return *this;
	}
	Nodeindex operator+=(const int& AddValue)
	{
		_x += AddValue;
		_y += AddValue;
		return *this;
	}
	Nodeindex& operator+=(const Nodeindex& nIndex)
	{
		this->_x += nIndex._x;
		this->_y += nIndex._y;
		return *this;
	}
	bool operator == (const Nodeindex& nIndex)
	{
		return ((_x == nIndex._x) && (_y == nIndex._y));
	}
	Nodeindex operator+ (const Nodeindex& nIndex)
	{
		Nodeindex rn;
		rn._x = this->_x + nIndex._x;
		rn._y = this->_y + nIndex._y;
		return rn;
	}
	Nodeindex(const int& x = 0, const int& y = 0) : _x(x), _y(y)
	{}
	int _x, _y;
};