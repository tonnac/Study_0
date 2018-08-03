#include <windows.h>

int WINAPI wWinMain(HINSTANCE hins, HINSTANCE hprev, LPWSTR szCmdLine, int iCmdShow)
{
	MessageBox(nullptr, L"Hello, Windows98!", L"HelloMsg", MB_ICONWARNING);

	return 0;
}