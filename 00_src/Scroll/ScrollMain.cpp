#include "Core.h"
#include "KbkObject.h"
#include "NPCObj.h"
#include "EndScene.h"
#include "Button.h"
#include <memory>

class KSample : public KCore
{
	std::shared_ptr<Scene>  m_pGameScene;
	std::shared_ptr<Scene>  m_pLobbyScene;
	std::shared_ptr<Scene>  m_pCEndScene;
	Scene*					m_pCurrentScene;
	int						m_iLevel;
public:
	bool Init()
	{
		m_iLevel = 1;
		m_pGameScene = std::make_shared<SceneGame>();
		m_pLobbyScene = std::make_shared<SceneLobby>();
		m_pCEndScene = std::make_shared<EndScene>();
		m_pCurrentScene = m_pLobbyScene.get();
		m_pGameScene->Init();
		m_pLobbyScene->Init();
		m_pCEndScene->Init();
		return true;
	}
	bool Frame()
	{
		switch (m_pCurrentScene->m_iSceneID)
		{
		case GameScene::SCENE_LOBBY:
			if (m_pCurrentScene->m_bNextSceneStart)
			{
				m_pCurrentScene->m_bNextSceneStart = false;
				m_pCurrentScene = m_pGameScene.get();
			}
			break;
		case GameScene::SCENE_PLAY:
			if (m_pCurrentScene->m_bNextSceneStart)
			{
				if (++m_iLevel > g_iMaxLevel)
				{
					m_pCurrentScene = m_pCEndScene.get();
					m_pCurrentScene->SetNpcCount(m_iLevel * 50);
					m_pCurrentScene->Reset();
					m_iLevel = 0;
				}
				else
				{
					//				m_pCurrentScene = m_pLobbyScene;
					m_pCurrentScene->SetNpcCount(m_iLevel * 50);
					m_pCurrentScene->Reset();
				}
			}
			break;
		case GameScene::SCENE_END:
			break;
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