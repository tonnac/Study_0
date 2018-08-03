#include "Win_01.h"
#include "Core.h"
class Simple : public Core
{};

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE prevInst, LPWSTR szCmdLine, int iCmdShow)
{
	Simple w1;
	w1.SetWindow(hInst);
	w1.Run();
	return 0;
}