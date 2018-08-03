#pragma once
#include <windows.h>
#include <assert.h>
#include <tchar.h>

extern HWND g_hWnd;

#define GAMESTART int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hprev, LPWSTR szCmdLine, int iCmdShow){
#define GAMERUN(s,w,h) Window win; win.SetWindow(hInst,L#s,w,h); win.Run();
#define GAMEEND 	return 0; }
