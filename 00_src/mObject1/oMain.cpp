#include "Core.h"
#include "KbkObject.h"



class KSample : public KCore
{
	KObject m_oHero;
	KbkObject m_bBackGround;
public:
	bool Init()
	{
		m_bBackGround.LoadFile(L"../../data/Domino.bmp");
		m_oHero.LoadFile(L"../../data/86754.bmp", L"../../02_data/86755.bmp");
		m_oHero.Set(100, 100, 1, 75, 48, 48);
		m_bBackGround.Set(0, 0, 0, 0, 1024, 768);
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
		rt.right = 200;
		rt.bottom = 200;
		rt.left = 100;
		rt.top = 100;
		m_bBackGround.Render();
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