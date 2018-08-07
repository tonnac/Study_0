#include "Core.h"
#include "KBKObject.h"

class KSample : public KCore
{
	KBKObject m_BackGround;
	KObject m_Hero;
public:
	bool				Init() override
	{
//		m_BackGround.Init();
//		m_BackGround.Set(0, 0, 0, 0, 800, 600);
//		m_BackGround.Load(L"../../01_data/Number.bmp");
		m_Hero.Set(m_Hero.m_pos.x, m_Hero.m_pos.y, 1, 75, 47, 48);
		m_Hero.Load(L"../../01_data/86754.bmp", L"../../01_data/86755.bmp");
		return true;
	}
	bool				Frame() override
	{
//		m_BackGround.Frame();
		m_Hero.Frame();
		return true;
	}
	bool				Render() override
	{
		static DWORD frame;
	//	m_BackGround.Draw(LR_ROTATION,&m_BackGround.m_rtDraw);
	//	m_Hero.DrawColorKey(RGB(255, 255, 255));
//		m_BackGround.Render();
		m_Hero.Render();
		frame = (++frame) % 7;
		m_Hero.Set(m_Hero.m_pos.x, m_Hero.m_pos.y, 1+frame+(frame*48), 75, 47, 48);
		return true;
	}
	bool				Release() override
	{
//		m_BackGround.Release();
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