#include "Core.h"
#include "KbkObject.h"



class KSample : public KCore
{
	KObject m_oHero;
	KbkObject m_bBackGround;
public:
	bool Init()
	{
		m_bBackGround.LoadFile(L"../../data/bk.bmp");
		m_oHero.LoadFile(L"../../data/86754.bmp", L"../../data/86755.bmp");
		m_oHero.Set(100, 100, 1, 75, 48, 48);
		m_bBackGround.Set(0, 0, 0, 0, 800, 600);
		m_bBackGround.Init();
		m_oHero.Init();
		return true;
	}
	bool Frame()
	{
		m_bBackGround.Frame();
		m_oHero.Frame();
		return true;
	}
	bool Render()
	{
		RECT rt;
		rt.right = 1024;
		rt.bottom = 768;
		rt.left = 0;
		rt.top = 0;
		m_bBackGround.Draw(0, &rt);
		m_oHero.Render();
		//m_oHero.Draw(LR_ROTATION, &rt);
		return true;
	}
	bool Release()
	{
		m_bBackGround.Release();
		m_oHero.Release();
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