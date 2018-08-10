#include "Core.h"
#include "KbkObject.h"
#include "NPCObj.h"
#include "EndScene.h"
#include "Button.h"
#include <memory>


using RECT_ARRAY = std::vector<RECT>;

class EffectObj : public NPCObj
{
	int iCurrentSprite;
	float tSpriteTime;
	float tOffset;
	RECT_ARRAY			m_rtSprite;
	int	m_iIndexSprite;
public:
	EffectObj()
	{
		int iCurrentSprite;
		float tSpriteTime;
		float tOffset;
		int	m_iIndexSprite = rand() % 3;
	}
public:
	void Set(RECT_ARRAY& rtSpriteList)
	{
		m_rtSprite = rtSpriteList;
	}
	bool Init()
	{
		tOffset = 1.0f / m_rtSprite.size();
	}
	bool Frame()
	{
		tSpriteTime += g_fSecPerFrame;
		if (tSpriteTime >= tOffset)
		{
			iCurrentSprite++;
			if (iCurrentSprite >= m_rtSprite.size())
			{
				iCurrentSprite = 0;
			}
			tSpriteTime -= tOffset;
		}
		RECT rt = m_rtSprite[iCurrentSprite];
		m_rtDraw = rt;
	}
};

class KSample : public KCore
{
	std::shared_ptr<Scene>				m_pGameScene;
	NPCObj								m_tmpObj;
	KObject								m_effect;
	float								m_fAngle;
	EffectObj							m_rtSpriteList[3];
public:
	bool GameDataLoad(const TCHAR* pszFile)
	{
		TCHAR pBuffer[256] = { 0, };
		TCHAR pTemp[256] = { 0, };

		int iNumSprite;
		FILE * fp_src;
		_wfopen_s(&fp_src, pszFile, _T("rt"));

		if (fp_src == nullptr) return false;

		_fgetts(pBuffer, _countof(pBuffer), fp_src);
		_stscanf_s(pBuffer, _T("%s%d%d"),
			pTemp, _countof(pTemp), &iNumSprite);
		m_rtSpriteList.resize(iNumSprite);
		for (int iCnt = 0; iCnt < iNumSprite; iCnt++)
		{
			//º¤ÅÍ¿¡ ÀúÀå~
		}

		fclose(fp_src);
		return true;
	}
	bool Init()
	{
		GameDataLoad(L"SpriteList.txt");


		m_fAngle = 0.0f;
		m_effect.Init();
		m_tmpObj.Init();
		m_tmpObj.LoadFile(L"../../data/bitmap1.bmp", L"../../data/bitmap2.bmp");
		m_effect.LoadFile(L"../../data/bitmap1.bmp", L"../../data/bitmap2.bmp");
		m_tmpObj.Set(500, 500, 133, 1, 42, 59);
		m_effect.Set(300, 300, 1, 142, 41, 41);

		m_pGameScene = std::make_shared<SceneGame>();

		m_pGameScene->Init();
		return true;
	}
	bool Frame()
	{
		static int iCurrentSprite = 0;
		static float tSpriteTime = 0.0f;
		float tOffset = 0.0f;
		tOffset = m_rtSpriteList[0].size() / 12.0f;

		tSpriteTime += g_fSecPerFrame;
		if (tSpriteTime >= tOffset)
		{
			iCurrentSprite++;
			if (iCurrentSprite >= m_rtSpriteList[0].size())
			{
				iCurrentSprite = 0;
			}
			tSpriteTime -= tOffset;
		}
		RECT rt = m_rtSpriteList[0][iCurrentSprite];

		m_fAngle += g_fSecPerFrame * 100.0f;
		m_pGameScene->Frame();
		
		m_tmpObj.Frame();
		m_effect.Frame();
		return true;
	}
	bool Render()
	{
		m_pGameScene->Render();
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