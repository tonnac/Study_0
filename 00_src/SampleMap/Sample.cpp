#include "TCore.h"
#include "TScene.h"
#include "TEnemy.h"

const int g_iMaxNPC = 30;
class Sample : public TCore
{
	std::shared_ptr<TScene>		m_pGameScene;	
	bool		m_bGameSceneChange;
public:
	bool	Init()
	{	
		m_bGameSceneChange = false;
		m_pGameScene = std::make_shared<TSceneGame>();
		m_pGameScene->Init();
		m_pGameScene->SetNpcCount(g_iMaxNPC);
		return true;
	}

	bool	Frame()
	{
		m_pGameScene->Frame();			
		return true;
	}
	bool	Render()
	{		
		if (m_bGameSceneChange == false)
			m_pGameScene->Render();
		else
			m_pGameScene->FadeOut();			

		m_bGameSceneChange = true;
		for (int inpc = 0; inpc < 
			m_pGameScene->m_iMaxNpcCount;
			inpc++)
		{
			if (!m_pGameScene->GetNpcDead(inpc))
			{
				m_bGameSceneChange = false;
			}
		}
		return true;
	}
	bool	Release()
	{		
		m_pGameScene->Release();		
		return true;
	}
public:
	Sample() {
	}
	virtual ~Sample() {}
};


GAME_RUN("SampleMap", 800, 600)