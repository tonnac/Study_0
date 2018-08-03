#include "KWindow.h"



int WINAPI wWinMain(HINSTANCE hinst, HINSTANCE preinst, LPWSTR szCmdline, int cmd)
{
	KWindow wd(hinst);
	wd.Init();

	return 0;
}