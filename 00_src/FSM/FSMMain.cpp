#include "Core.h"
#include "KbkObject.h"
#include "ZEnemy.h"
#include "Scene.h"

class KSample : public KCore
{
	ZEnemy								m_tmpObj;
	Hero								m_effect;
	float								m_fAngle;
public:
	bool Init()
	{
		m_fAngle = 30.0f;
		m_effect.Init();
		m_tmpObj.Init();
		m_tmpObj.LoadFile(L"../../data/bitmap1.bmp", L"../../data/bitmap2.bmp");
		m_effect.LoadFile(L"../../data/bitmap1.bmp", L"../../data/bitmap2.bmp");
		m_tmpObj.Set(500, 500, 133, 1, 42, 59);
		m_effect.Set(300, 300, 133, 1, 42, 59);


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