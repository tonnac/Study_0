#include "Core.h"
#include "KBKObject.h"

class KSample : public KCore
{
	KBKObject m_BackGround;
	KObject m_Hero;
public:
	bool				Init()
	{
		m_BackGround.Init();
		m_BackGround.Set(0, 0, 0, 0, 800, 600);
		m_BackGround.Load(L"../../01_data/Number.bmp");
		m_Hero.Set(300, 300, 90, 2, 130, 60);
		m_Hero.Load(L"../../01_data/Number.bmp");
		return true;
	}
	bool				Frame()
	{
		m_BackGround.Frame();
		m_Hero.Frame();
		return true;
	}
	bool				Redner()
	{
	//	m_BackGround.Draw(LR_ROTATION,&m_BackGround.m_rtDraw);
	//	m_Hero.DrawColorKey(RGB(255, 255, 255));
		m_BackGround.Render();
		m_Hero.Render();
		return true;
	}
	bool				Release()
	{
		m_BackGround.Release();
		m_Hero.Release();
		return true;
	}
private:
};



int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE prevhInst, LPWSTR szCmdLine, int nCmdShow)
{
	KSample wd;
	wd.SetWindow(hInst);
	wd.Run();
	return 0;
}