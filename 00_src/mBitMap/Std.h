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

extern HWND			g_hWnd;				//Ÿ�̸�::�����Լ����� ���
extern HINSTANCE	g_hInstance;		//��Ʈ��::�ε��Լ����� ���
extern float		g_fSecPerFrame;
extern HDC			g_hOffScreenDC;