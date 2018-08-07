#include "Core.h"
#include "KbkObject.h"
#include "NPCObj.h"

const int g_iMaxNpcCount = 10;

class KSample : public KCore
{
	std::vector<NPCObj>	m_npcList;
	KObject				m_Hero;
	KbkObject			m_BackGround;
public:
	bool Init()
	{
		m_npcList.resize(g_iMaxNpcCount);
		for (int iObj = 0; iObj < g_iMaxNpcCount; iObj++)
		{
			m_npcList[iObj].LoadFile(L"../../data/bitmap1.bmp", L"../../data/bitmap2.bmp");
			m_npcList[iObj].Set(static_cast<float>(100.0 + rand() % 500), 100 + rand() % 100, 115, 62, 36, 35);
			m_npcList[iObj].Init();
		}
		m_BackGround.LoadFile(L"../../data/bk.bmp");
		m_Hero.LoadFile(L"../../data/bitmap1.bmp", L"../../data/bitmap2.bmp");
		m_Hero.Set(500, 500, 133, 1, 42, 59);
		m_BackGround.Set(0, 0, 0, 0, 800, 600);
		m_BackGround.Init();
		m_Hero.Init();
		return true;
	}
	bool Frame()
	{
		if (I_KInput.getKey('0') == KEY_PUSH)
		{
			m_Hero.m_bDebugRect = !m_Hero.m_bDebugRect;
			for (int iObj = 0; iObj < g_iMaxNpcCount; iObj++)
			{
				m_npcList[iObj].m_bDebugRect = !m_npcList[iObj].m_bDebugRect;
			}
		}
		m_BackGround.Frame();
		m_Hero.Frame();
		for (int iObj = 0; iObj < g_iMaxNpcCount; iObj++)
		{
			m_npcList[iObj].Frame();
		}

		return true;
	}
	bool Render()
	{
		m_BackGround.Render();
		for (int iObj = 0; iObj < g_iMaxNpcCount; iObj++)
		{
			m_npcList[iObj].Render();
		}
		m_Hero.Render();
		return true;
	}
	bool Release()
	{
		for (int iObj = 0; iObj < g_iMaxNpcCount; iObj++)
		{
			m_npcList[iObj].Release();
		}
		m_BackGround.Release();
		m_Hero.Release();
		return true;
	}
private:
};



int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE prevhInst, LPWSTR szCmdLine, int nCmdShow)
{
	KSample wd;
	wd.SetWindow(hInst,800,600);
	wd.Run();
	return 0;
}