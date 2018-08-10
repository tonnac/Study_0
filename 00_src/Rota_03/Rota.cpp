#include "Core.h"
#include "KbkObject.h"
#include "NPCObj.h"
#include "EndScene.h"
#include "Button.h"
#include <memory>


class KSample : public KCore
{
	KObject kobj;
	float fAngle;
public:
	bool Init()
	{
		fAngle = 0;
		kobj.Init();
		kobj.LoadFile(L"../../data/bitmap1.bmp", L"../../data/bitmap2.bmp");
		kobj.Set(500, 500, 133, 1, 42, 59);

		return true;
	}
	bool Frame()
	{
		fAngle += g_fSecPerFrame * 100.0f;
		kobj.Frame();
		return true;
	}
	bool Render()
	{

		kobj.RotationBlt(fAngle);
		return true;
	}
	bool Release()
	{
		kobj.Release();
		return true;
	}
private:
};



int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE prevhInst, LPWSTR szCmdLine, int nCmdShow)
{
	KSample wd;
	wd.SetWindow(hInst, 800, 600);
	wd.Run();
	return 0;
}