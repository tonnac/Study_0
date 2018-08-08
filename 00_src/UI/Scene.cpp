#include "Scene.h"
#include "Collision.h"

bool SceneGame::Reset()
{
	for (int iObj = 0; iObj < g_iMaxNpcCount; iObj++)
	{
		m_npcList[iObj].m_bDead = false;
		m_npcList[iObj].Set(
			static_cast<float>(100.0 + rand() % 500),
			static_cast<float>(100 + rand() % 100),
			115, 62, 36, 35);
	}
	m_bNextSceneStart = false;
	return true;
}

bool SceneGame::Init()
{
	m_npcList.resize(g_iMaxNpcCount);
	for (int iObj = 0; iObj < g_iMaxNpcCount; iObj++)
	{
		m_npcList[iObj].LoadFile(L"../../data/bitmap1.bmp", L"../../data/bitmap2.bmp");
		m_npcList[iObj].Set(
			static_cast<float>(100.0 + rand() % 500),
			static_cast<float>(100 + rand() % 100),
			115, 62, 36, 35);
		m_npcList[iObj].Init();
	}
	m_BackGround.LoadFile(L"../../data/binglybongly_wallpaper.bmp");
	m_Hero.LoadFile(L"../../data/bitmap1.bmp", L"../../data/bitmap2.bmp");
	m_Hero.Set(500, 500, 133, 1, 42, 59);
	m_BackGround.Set(g_rtClient.right / 2, g_rtClient.bottom / 2, 0, 0, 800, 600);
	m_BackGround.Init();
	m_Hero.Init();
	return true;
}

bool SceneGame::Frame()
{
	if (I_KInput.getKey('0') == KEY_PUSH)
	{
		m_Hero.m_bDebugRect = !m_Hero.m_bDebugRect;
		for (int iObj = 0; iObj < m_iMaxNpcCount; iObj++)
		{
			m_npcList[iObj].m_bDebugRect = !m_npcList[iObj].m_bDebugRect;
		}
	}
	m_BackGround.Frame();

	for (int iObj = 0; iObj < m_iMaxNpcCount; iObj++)
	{
		m_npcList[iObj].Frame();
	}
	bool bChangeScene = true;
	for (int iNpc = 0; iNpc < m_iMaxNpcCount; ++iNpc)
	{
		if (Collision::RectInRect(m_npcList[iNpc].m_rtCollision, m_Hero.m_rtCollision))
		{
			m_npcList[iNpc].m_bDead = true;
		}
		if (I_KInput.getMouse(VK_LBUTTON) && Collision::SphereInPt(m_npcList[iNpc].m_rtCollision, I_KInput.m_MousePos))
		{
			m_npcList[iNpc].m_bDead = true;
		}
		if(m_npcList[iNpc].m_bDead == false)
		{
			bChangeScene = false;
		}
	}
	if (I_KInput.getMouse(VK_RBUTTON) == KEY_UP)
	{
		for (int i = 0; i < m_iMaxNpcCount; ++i)
		{
			m_npcList[i].m_bDead = true;
		}
	}
	if (bChangeScene == true)
	{
		m_bNextSceneStart = true;
	}
	m_Hero.Frame();

	return true;
}
bool SceneGame::Render()
{
	m_BackGround.Render();
	for (int iObj = 0; iObj < m_iMaxNpcCount; iObj++)
	{
		if (!m_npcList[iObj].m_bDead)
		{
			m_npcList[iObj].Render();
		}
	}
	m_Hero.Render();
	return true;
}

bool SceneGame::Release()
{
	for (int iObj = 0; iObj < m_iMaxNpcCount; iObj++)
	{
		m_npcList[iObj].Release();
	}
	m_BackGround.Release();
	m_Hero.Release();
	return true;
}



Scene::Scene()
{
	m_iSceneID = 1;
	m_bNextSceneStart = false;
	m_iMaxNpcCount = 10;
}


Scene::~Scene()
{
}
