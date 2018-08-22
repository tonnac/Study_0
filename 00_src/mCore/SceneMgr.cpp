#include "SceneMgr.h"

SceneMgr::SceneMgr() : m_nIndex(5)
{
}

bool SceneMgr::Init()
{
	m_pCurrentScene = CreateScene(5, true);
	return true;
}
bool SceneMgr::Frame()
{
	if (!m_pCurrentScene->Frame())
	{
		bool bflag = m_pCurrentScene->getNextScene();
		m_pCurrentScene->Release();
		delete m_pCurrentScene;
		if (bflag)
		{
			m_pCurrentScene = CreateScene(++m_nIndex, bflag);
		}
		else
		{
			m_pCurrentScene = CreateScene(--m_nIndex, bflag);
		}
	}
	return true;
}
bool SceneMgr::Render()
{
	m_pCurrentScene->Render();
	return true;
}
bool SceneMgr::Release()
{
	m_pCurrentScene->Release();
	return true;
}
Scene* SceneMgr::CreateScene(const INT& index, const bool& bNextScene)
{
	Scene * pScene = nullptr;
	switch (index)
	{
	case 0:
		pScene = New LobbyScene;
		break;
	case 1:
		pScene = New GameScene1;
		break;
	case 2:
		pScene = New GameScene2;
		break;
	case 3:
		pScene = New GameScene3;
		break;
	case 4:
		pScene = New GameScene4;
		break;
	case 5:
		pScene = New GameScene5;
		break;
	}
	pScene->Init();
	if (!bNextScene)
	{
		pScene->inverseSet();
	}
	return pScene;
}