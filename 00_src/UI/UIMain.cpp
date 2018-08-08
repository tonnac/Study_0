#include "Core.h"
#include "KbkObject.h"
#include "NPCObj.h"
#include "EndScene.h"
#include "Button.h"


class KSample : public KCore
{
	Scene*					m_pGameScene;
	Scene*					m_pLobbyScene;
	Scene*					m_pCEndScene;
	Scene*					m_pCurrentScene;
	int						m_iLevel;
public:
	bool Init()
	{
		m_iLevel = 1;
		m_pGameScene = new SceneGame;
		m_pLobbyScene = new SceneLobby;
		m_pCEndScene = new EndScene;
		m_pCurrentScene = m_pGameScene;
		m_pGameScene->Init();
		m_pLobbyScene->Init();
		m_pCEndScene->Init();
		return true;
	}
	bool Frame()
	{
		switch (m_pCurrentScene->m_iSceneID)
		{
		case 0:
			if (m_pCurrentScene->m_bNextSceneStart)
			{
				m_pCurrentScene->m_bNextSceneStart = false;
				m_pCurrentScene = m_pGameScene;
			}
			break;
		case 1:
			if (m_pCurrentScene->m_bNextSceneStart)
			{
				if (++m_iLevel > g_iMaxNpcCount / 10)
				{
					m_pCurrentScene = m_pCEndScene;
					m_pCurrentScene->m_iMaxNpcCount = m_iLevel * 10;
					m_pCurrentScene->Reset();
					m_iLevel = 0;
				}
				else
				{
					m_pCurrentScene = m_pLobbyScene;
					m_pCurrentScene->m_iMaxNpcCount = m_iLevel * 10;
					m_pCurrentScene->Reset();
				}
			}
		}
		m_pCurrentScene->Frame();

		return true;
	}
	bool Render()
	{
		m_pCurrentScene->Render();
		return true;
	}
	bool Release()
	{
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