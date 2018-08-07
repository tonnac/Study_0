#include "Core.h"
#include "KbkObject.h"
#include "NPCObj.h"

const int g_iMaxNpcCount = 10;

class KSample : public KCore
{
	std::vector<NPCObj>	m_npcList;
	KObject				m_oHero;
	KbkObject			m_bBackGround;
public:
	bool Init()
	{
		m_npcList.resize(10);
		for (int iObj = 0; iObj < g_iMaxNpcCount; iObj++)
		{
			m_npcList[iObj].LoadFile();
			m_npcList[iObj].Set(100 + rand() % 600, 100 + rand() % 700, 46, 62, 68, 79);
			m_npcList[iObj].Init();
		}
		m_bBackGround.LoadFile(L"../../data/bk.bmp");
		m_oHero.LoadFile(L"../../data/86754.bmp", L"../../data/86755.bmp");
		m_oHero.Set(100, 100, 1, 75, 48, 48);
		m_bBackGround.Set(g_rtClient.right / 2, g_rtClient.bottom / 2, 0, 0, 800, 600);
		m_bBackGround.Init();
		m_oHero.Init();
		return true;
	}
	bool Frame()
	{
		if (I_KInput.getKey('0') == KEY_PUSH)
		{
			m_oHero.m_bDebugRect = !m_oHero.m_bDebugRect;
			for (int iObj = 0; iObj < g_iMaxNpcCount; iObj++)
			{
				m_npcList[iObj].m_bDebugRect = !m_npcList[iObj].m_bDebugRect;
			}
		}
		m_bBackGround.Frame();
		m_oHero.Frame();
		for (int iObj = 0; iObj < g_iMaxNpcCount; iObj++)
		{
			m_npcList[iObj].Frame();
		}
//		m_npc.Frame();
		return true;
	}
	bool Render()
	{
		RECT rt;
		rt.right = 1024;
		rt.bottom = 768;
		rt.left = 0;
		rt.top = 0;
		for (int iObj = 0; iObj < g_iMaxNpcCount; iObj++)
		{
			m_npcList[iObj].Render();
		}

		m_bBackGround.Draw(0, &rt);
		m_oHero.Render();
//		m_npc.Render();
		//m_oHero.Draw(LR_ROTATION, &rt);
		return true;
	}
	bool Release()
	{
		for (int iObj = 0; iObj < g_iMaxNpcCount; iObj++)
		{
			m_npcList[iObj].Release();
		}
		m_bBackGround.Release();
		m_oHero.Release();
//		m_npc.Release();
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