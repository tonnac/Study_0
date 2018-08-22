#include "Core.h"
#include "BkObject.h"
#include "ZEnemy.h"
#include "Scene.h"
#include "ZFsmMgr.h"

class KSample : public Core
{
	ZEnemy								m_tmpObj;
	Hero								m_effect;
	float								m_fAngle;
public:
	bool Init()
	{
		I_ZFsmMgr.Load(L"fsmDefault.txt");
		I_ZFsmMgr.Load(L"fsmLevel1.txt");
		m_fAngle = 30.0f;
		m_effect.Init();
		m_tmpObj.Init();
		m_tmpObj.LoadFile(L"../../data/bitmap1.bmp", L"../../data/bitmap2.bmp");
		m_effect.LoadFile(L"../../data/bitmap1.bmp", L"../../data/bitmap2.bmp");
		m_tmpObj.Set(500, 500, 133, 1, 42, 59);
		m_effect.Set(300, 300, 133, 1, 42, 59);

		m_tmpObj.SetFsm(rand() % I_ZFsmMgr.getSize() + 1);
		return true;
	}
	bool Frame()
	{
		m_fAngle += g_fSecPerFrame * 30.0f;
		m_effect.Frame();
		m_tmpObj.Process(&m_effect);
		return true;
	}
	bool Render()
	{
		m_effect.Render();
		m_tmpObj.RotationBlt(m_fAngle);
		return true;
	}
	bool Release()
	{
		m_effect.Release();
		m_tmpObj.Release();
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