#include "GameScene.h"
#include "Rendering.h"
#include "DownableObject.h"

GameScene::GameScene() : m_pScroll(&m_pPlayer,&m_BKObject), m_pFadeObject(nullptr)
{}
bool GameScene::Init()
{
	m_pFadeObject = New FadeObject;
	m_pFadeObject->Set(0,0,0,0,g_rtClient.right,g_rtClient.bottom);
	m_pFadeObject->Init();

	S_SpriteMgr.SpriteSet(L"../../data/txt/Kaho.txt");
	m_pPlayer.LoadFile(L"PLAYER", L"../../data/bmp/KahoColor.bmp", L"../../data/bmp/KahoMask.bmp");
	m_BKObject.LoadFile(L"BACKGROUND", L"../../data/bmp/Map.bmp");
	m_BKObject.Set(0, 0, 0, 0, 2072, 772);
	m_BKObject.Init();

	TerrainObject * t1 = New TerrainObject;
	t1->Set(0, 622, 0, 622, 1560, 150);
	m_BKObject.AddTerrain(t1);

	t1 = New TerrainObject;
	t1->Set(1560, 568, 1560, 568, 103, 204);
	m_BKObject.AddTerrain(t1);

	t1 = New TerrainObject;
	t1->Set(1663, 468, 1663, 468, 155, 304);
	m_BKObject.AddTerrain(t1);

	t1 = New TerrainObject;
	t1->Set(1818, 623, 1818, 623, 335, 151);
	m_BKObject.AddTerrain(t1);

	m_pPlayer.Set(150, 580, 10, 87, 25, 36);
	m_pPlayer.Init();
	m_pPlayer.setRendering(2.8f, INVERSE::DEFAULT);

	m_pScroll.Init();

	return true;
}
bool GameScene::Frame()
{
	const FloatPoint px = *m_pPlayer.getDrawPos();
	if (px.x >= 900)
	{
		m_bNextSceneStart = true;
		return false;
	}
	if (m_BKObject.Collision(&m_pPlayer) == false)
	{
		m_BKObject.setRendering();
	}
	m_pPlayer.Frame();
	m_pScroll.Frame();
	if (m_pFadeObject)
	{
		if (!m_pFadeObject->Frame())
		{
			delete m_pFadeObject;
			m_pFadeObject = nullptr;
		}
	}

	return true;
}
bool GameScene::Render()
{
	m_BKObject.Render();
	m_pScroll.Render();
	m_pPlayer.Render();
	if (m_pFadeObject)
	{
		m_pFadeObject->Render();
	}
	return true;
}
bool GameScene::Release()
{
	m_pPlayer.Release();
	m_BKObject.Release();
	return true;
}
bool GameScene::inverseSet()
{
	m_pFadeObject = New FadeObject;
	m_pFadeObject->Set(0, 0, 0, 0, g_rtClient.right, g_rtClient.bottom);
	m_pFadeObject->Init();

	m_BKObject.ReverseSet();

	m_pPlayer.Set(800, 580, 10, 87, 25, 36);
	m_pPlayer.setRendering(2.8f, INVERSE::LR_ROTATION);
	m_pPlayer.setDir(-1);

	return true;
}
GameScene2::GameScene2() : m_pScroll(&m_pPlayer, &m_BKObject), m_pFadeObject(nullptr)
{}
bool GameScene2::Init()
{
	m_pFadeObject = New FadeObject;
	m_pFadeObject->Set(0, 0, 0, 0, g_rtClient.right, g_rtClient.bottom);
	m_pFadeObject->Init();

	S_SpriteMgr.SpriteSet(L"../../data/txt/Kaho.txt");
	m_pPlayer.LoadFile(L"PLAYER", L"../../data/bmp/KahoColor.bmp", L"../../data/bmp/KahoMask.bmp");
	m_BKObject.LoadFile(L"BACKGROUND", L"../../data/bmp/Map.bmp");
	m_BKObject.Set(0, 0, 2072, 0, 2206, 769);
	m_BKObject.Init();

	TerrainObject * t1 = New TerrainObject;
	t1->Set(0, 620, 0, 620, 740, 148);
	m_BKObject.AddTerrain(t1);

	t1 = New TerrainObject;
	t1->Set(728, 414, 728, 414, 106, 355);
	m_BKObject.AddTerrain(t1);

	t1 = New DownableObject;
	t1->Set(627, 467, 627, 467, 101, 21);
	m_BKObject.AddTerrain(t1);

	//t1 = New TerrainObject;
	//t1->Set(1818, 623, 1818, 623, 335, 151);
	//m_BKObject.AddTerrain(t1);

	m_pPlayer.Set(130, 580, 10, 87, 25, 36);
	m_pPlayer.Init();
	m_pPlayer.setRendering(2.8f, INVERSE::DEFAULT);

	m_pScroll.Init();

	return true;
}
bool GameScene2::Frame()
{
	const FloatPoint px = *m_pPlayer.getDrawPos();
	if (px.x <= 20)
	{
		m_bNextSceneStart = false;
		return false;
	}
	if (px.x >= 900)
	{
		m_bNextSceneStart = true;
		return false;
	}
	if (m_BKObject.Collision(&m_pPlayer) == false)
	{
		m_BKObject.setRendering();
	}
	m_pPlayer.Frame();
	m_pScroll.Frame();
	if (m_pFadeObject)
	{
		if (!m_pFadeObject->Frame())
		{
			delete m_pFadeObject;
			m_pFadeObject = nullptr;
		}
	}
	return true;
}
bool GameScene2::Render()
{
	m_BKObject.Render();
	m_pPlayer.Render();
	m_pScroll.Render();
	if (m_pFadeObject)
	{
		m_pFadeObject->Render();
	}
	return true;
}
bool GameScene2::Release()
{
	m_pPlayer.Release();
	m_BKObject.Release();
	return true;
}
bool GameScene2::inverseSet()
{
	m_pFadeObject = New FadeObject;
	m_pFadeObject->Set(0, 0, 0, 0, g_rtClient.right, g_rtClient.bottom);
	m_pFadeObject->Init();

	m_BKObject.ReverseSet();

	m_pPlayer.Set(800, 580, 10, 87, 25, 36);
	m_pPlayer.setRendering(2.8f, INVERSE::LR_ROTATION);
	m_pPlayer.setDir(-1);

	return true;
}