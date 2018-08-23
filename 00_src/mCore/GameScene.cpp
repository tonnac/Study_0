#include "GameScene.h"
#include "Rendering.h"
#include "DownableObject.h"
#include "LadderObject.h"
#include "Enemy.h"
#include "TrapObject.h"
#include "OrbObject.h"
#include "ScrollObject.h"
#include "PlatObject.h"

FadeObject* GameScene5::m_fDeadScene = nullptr;

GameScene::GameScene() : m_pScroll(&m_pPlayer, &m_BKObject, &m_NPCList)
{}

GameScene1::GameScene1()
{}
bool GameScene1::Init()
{
	m_pFadeObject = New FadeObject;
	m_pFadeObject->Set(0,0,0,0,g_rtClient.right,g_rtClient.bottom);
	m_pFadeObject->Init();

	S_SpriteMgr.SpriteSet(L"../../data/txt/Kaho.txt");
	m_pPlayer.LoadFile(L"PLAYER", L"../../data/bmp/KahoColor.bmp", L"../../data/bmp/KahoMask.bmp");
	m_BKObject.LoadFile(L"BACKGROUND", L"../../data/bmp/Map.bmp");
	m_BKObject.Set(0, 0, 0, 0, 2072, 772);
	m_BKObject.Init();
	
	m_BKObject.AddUI(g_UI);
	m_BKObject.AddUI(g_HPBar);

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

	m_pPlayer.Set(150, 300, 10, 87, 25, 36);
	m_pPlayer.Init();
	m_pPlayer.setRendering(2.8f, INVERSE::DEFAULT);

	m_pScroll.Init();

	return true;
}
bool GameScene1::Frame()
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
bool GameScene1::Render()
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
bool GameScene1::Release()
{
	m_pPlayer.Release();
	m_BKObject.Release();
	return true;
}
bool GameScene1::inverseSet()
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

GameScene2::GameScene2()
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

	m_BKObject.AddUI(g_UI);
	m_BKObject.AddUI(g_HPBar);

	TerrainObject * t1 = New TerrainObject;
	t1->Set(0, 620, 0, 620, 740, 148);
	m_BKObject.AddTerrain(t1);

	t1 = New TerrainObject;
	t1->Set(728, 414, 728, 414, 106, 355);
	m_BKObject.AddTerrain(t1);

	t1 = New DownableObject;
	t1->Set(627, 467, 627, 467, 101, 21);
	m_BKObject.AddTerrain(t1);

	t1 = New DownableObject;
	t1->Set(834, 415, 836, 415, 207, 21);
	m_BKObject.AddTerrain(t1);

	t1 = New TerrainObject;
	t1->Set(938, 622, 938, 622, 418, 147);
	m_BKObject.AddTerrain(t1);

	t1 = New TerrainObject;
	t1->Set(1351, 516, 1351, 516, 123, 220);
	m_BKObject.AddTerrain(t1);

	t1 = New TerrainObject;
	t1->Set(1406, 468, 1406, 468, 52, 301);
	m_BKObject.AddTerrain(t1);

	t1 = New TerrainObject;
	t1->Set(1457, 364, 1457, 364, 258, 405);
	m_BKObject.AddTerrain(t1);

	t1 = New TerrainObject;
	t1->Set(1041, 311, 1041, 311, 109, 160);
	m_BKObject.AddTerrain(t1);

	t1 = New TerrainObject;
	t1->Set(1150, 364, 1150, 364, 50, 105);
	m_BKObject.AddTerrain(t1);

	t1 = New DownableObject;
	t1->Set(1196, 362, 1196, 362, 262, 23);
	m_BKObject.AddTerrain(t1);

	t1 = New TerrainObject;
	t1->Set(1715, 674, 1715, 674, 600, 95);
	m_BKObject.AddTerrain(t1);

	t1 = New TerrainObject;
	t1->Set(1974, 0, 1974, 0, 232, 517);
	m_BKObject.AddTerrain(t1);

	t1 = New DownableObject;
	t1->Set(1715, 362, 1715, 362, 259, 23);
	m_BKObject.AddTerrain(t1);

	t1 = New LadderObject;
	t1->Set(1717, 362, 1717, 362, 50, 311);
	m_BKObject.AddTerrain(t1);

	m_pPlayer.Set(130, 580, 10, 87, 25, 36);
	m_pPlayer.Init();
	m_pPlayer.setRendering(2.8f, INVERSE::DEFAULT);

	m_pScroll.Init();

	return true;
}
bool GameScene2::Frame()
{
	//static float ftimer = 0.0f;

	//ftimer += g_fPerSecFrame;

	//if (ftimer <= 5.0f)
	//{
	//	FloatPoint pe = *m_pPlayer.getCenterPos();
	//	FloatPoint xy = *m_BKObject.getCenterPos();
	//	int i = rand() % 2 == 0 ? 1 : -1;
	//	float k = rand() % 5 * g_fPerSecFrame * 35.0f;
	//	m_BKObject.setCenterPos_x(xy.x + i * k);
	//	m_pPlayer.setCenterPos_x(pe.x + i * k);
	//	int y = rand() % 2 == 0 ? 1 : -1;
	//	float a = rand() % 5 * g_fPerSecFrame * 35.0f;
	//	m_BKObject.setCenterPos_y(xy.y + y * a);
	//	m_pPlayer.setCenterPos_y(pe.y + y * a);
	//}

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

GameScene3::GameScene3()
{}
bool GameScene3::Init()
{
	m_pFadeObject = New FadeObject;
	m_pFadeObject->Set(0, 0, 0, 0, g_rtClient.right, g_rtClient.bottom);
	m_pFadeObject->Init();

	S_SpriteMgr.SpriteSet(L"../../data/txt/Kaho.txt");
	m_pPlayer.LoadFile(L"PLAYER", L"../../data/bmp/KahoColor.bmp", L"../../data/bmp/KahoMask.bmp");
	m_BKObject.LoadFile(L"BACKGROUND", L"../../data/bmp/Map.bmp");
	m_BKObject.Set(0, 0, 4292, 0, 960, 720);
	m_BKObject.Init();

	m_BKObject.AddUI(g_UI);
	m_BKObject.AddUI(g_HPBar);

	TerrainObject * t1 = New TerrainObject;
	t1->Set(0, 673, 0, 673, 1010, 47);
	m_BKObject.AddTerrain(t1);

	t1 = New TerrainObject;
	t1->Set(376, 622, 376, 622, 209, 51);
	m_BKObject.AddTerrain(t1);

	t1 = New TerrainObject;
	t1->Set(0, 309, 0, 309, 66, 210);
	m_BKObject.AddTerrain(t1);

	t1 = New TerrainObject;
	t1->Set(0, 0, 0, 0, 960, 309);
	m_BKObject.AddTerrain(t1);

	t1 = New TerrainObject;
	t1->Set(894, 307, 894, 307, 66, 210);
	m_BKObject.AddTerrain(t1);

	m_pPlayer.Set(130, 580, 10, 87, 25, 36);
	m_pPlayer.Init();
	m_pPlayer.setRendering(2.8f, INVERSE::DEFAULT);

	m_pScroll.Init();

	return true;
}
bool GameScene3::Frame()
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
bool GameScene3::Render()
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
bool GameScene3::Release()
{
	m_pPlayer.Release();
	m_BKObject.Release();
	return true;
}
bool GameScene3::inverseSet()
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

GameScene4::GameScene4()
{}
bool GameScene4::Init()
{

	m_pFadeObject = New FadeObject;
	m_pFadeObject->Set(0, 0, 0, 0, g_rtClient.right, g_rtClient.bottom);
	m_pFadeObject->Init();

	S_SpriteMgr.SpriteSet(L"../../data/txt/Kaho.txt");
	S_SpriteMgr.SpriteSet(L"../../data/txt/Monkey.txt");
	m_pPlayer.LoadFile(L"PLAYER", L"../../data/bmp/KahoColor.bmp", L"../../data/bmp/KahoMask.bmp");
	m_BKObject.LoadFile(L"BACKGROUND", L"../../data/bmp/Map.bmp");
	m_BKObject.Set(0, 0, 5310, 0, 2198, 722);
	m_BKObject.Init();

	m_BKObject.AddUI(g_UI);
	m_BKObject.AddUI(g_HPBar);

	TerrainObject * t1 = New TerrainObject;
	t1->Set(0, 673, 0, 673, 2198, 48);
	m_BKObject.AddTerrain(t1);

	t1 = New TerrainObject;
	t1->Set(0, 0, 0, 0, 86, 517);
	m_BKObject.AddTerrain(t1);

	t1 = New TerrainObject;
	t1->Set(550, 572, 550, 572, 625, 102);
	m_BKObject.AddTerrain(t1);

	t1 = New TerrainObject;
	t1->Set(1535, 622, 1535, 622, 663, 52);
	m_BKObject.AddTerrain(t1);

	t1 = New DownableObject;
	t1->Set(1173, 570, 1173, 570, 105, 20);
	m_BKObject.AddTerrain(t1);

	Enemy * pl = New Enemy;
	pl->LoadFile(L"ENEMY", L"../../data/bmp/MonkeyColor.bmp", L"../../data/bmp/MonkeyMask.bmp");
	pl->Set(680, 550, 14, 66, 28, 23);
	pl->Init();
	pl->setRendering(2.8f, INVERSE::DEFAULT);
	FloatRect rt = { 554,100,1173,573 };
	pl->setArea(rt);
	m_NPCList.push_back(pl);
	
	pl = New Enemy;
	pl->LoadFile(L"ENEMY", L"../../data/bmp/MonkeyColor.bmp", L"../../data/bmp/MonkeyMask.bmp");
	pl->Set(1869, 600, 14, 66, 28, 23);
	pl->Init();
	pl->setRendering(2.8f, INVERSE::DEFAULT);
	rt = { 1670,219,2165,616 };
	pl->setArea(rt);
	m_NPCList.push_back(pl);

	m_pPlayer.Set(130, 400, 10, 87, 25, 36);
	m_pPlayer.Init();
	m_pPlayer.setRendering(2.8f, INVERSE::DEFAULT);
	m_pScroll.Init();

	return true;
}
bool GameScene4::Frame()
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
	m_BKObject.Collision(&m_pPlayer);

	for (NPCLIST it = m_NPCList.begin(); it != m_NPCList.end();)
	{
		m_BKObject.Collision(*it);
		(*it)->Process(&m_pPlayer);
		if ((*it)->isDead())
		{
			it = m_NPCList.erase(it);
		}
		else
		{
			it++;
		}
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
bool GameScene4::Render()
{
	m_BKObject.Render();
	for (auto it : m_NPCList)
	{
		it->Render();
	}
	m_pPlayer.Render();
	m_pScroll.Render();
	if (m_pFadeObject)
	{
		m_pFadeObject->Render();
	}

	return true;
}
bool GameScene4::Release()
{
	m_pPlayer.Release();
	m_BKObject.Release();
	for (auto it : m_NPCList)
	{
		it->Release();
	}
	return true;
}
bool GameScene4::inverseSet()
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

GameScene5::GameScene5()
{}
bool GameScene5::Init()
{
	g_UI = New UI;
	g_UI->LoadFile(L"UI", L"../../data/bmp/UIColor.bmp", L"../../data/bmp/UIMask.bmp");
	g_HPBar = New UI;
	g_HPBar->LoadFile(L"HPBAR", L"../../data/bmp/HPBar.bmp");
	g_UI->Set(30, 48, 0, 0, 276, 72);
	g_HPBar->Set(108, 51, 0, 0, 186, 21);
	g_UI->Init();
	g_HPBar->Init();

	m_pFadeObject = New FadeObject;
	m_pFadeObject->Set(0, 0, 0, 0, g_rtClient.right, g_rtClient.bottom);
	m_pFadeObject->Init();

	S_SpriteMgr.SpriteSet(L"../../data/txt/Kaho.txt");
	m_pPlayer.LoadFile(L"PLAYER", L"../../data/bmp/KahoColor.bmp", L"../../data/bmp/KahoMask.bmp");
	m_BKObject.LoadFile(L"BACKGROUND", L"../../data/bmp/Map.bmp");
	m_BKObject.Set(0, 0, 9073, 0, 2140, 720);
	m_BKObject.Init();

	m_BKObject.AddUI(g_UI);
	m_BKObject.AddUI(g_HPBar);

	TerrainObject * t1 = New TerrainObject;
	t1->Set(0, 622, 0, 622, 884, 98);
	m_BKObject.AddTerrain(t1);

	t1 = New DownableObject;
	t1->Set(884, 621, 884, 622, 105, 21);
	m_BKObject.AddTerrain(t1);

	t1 = New TrapObject;
	t1->Set(902, 688, 902, 688, 706, 32);
	m_BKObject.AddTerrain(t1);

	t1 = New TerrainObject;
	t1->Set(1607, 623, 1607, 623, 533, 97);
	m_BKObject.AddTerrain(t1);

	t1 = New TerrainObject;
	t1->Set(1607, 570, 1607, 570, 111, 52);
	m_BKObject.AddTerrain(t1);

	t1 = New OrbObject;
	t1->LoadFile(L"ORB", L"../../data/bmp/Orb.bmp");
	t1->Set(1609, 517, 0, 0, 56, 51);
	t1->Init();
	m_BKObject.AddTerrain(t1);

	ScrollObject * t2 = New ScrollObject;
	t2->Set(908, 547, 908, 547, 78, 73);
	m_BKObject.AddTerrain(t2);
	m_pScroll.AddScrollObject(t2);

	PlatObject * t3 = New PlatObject;
	t3->LoadFile(L"PLAT", L"../../data/bmp/Plat.bmp");
	t3->Set(1174, 818, 2, 96, 144, 144);
	t3->Init();
	m_BKObject.AddPlat(t3);

	t3 = New PlatObject;
	t3->LoadFile(L"PLAT", L"../../data/bmp/Plat.bmp");
	t3->Set(1318, 769, 146, 48, 144, 192);
	t3->Init();
	m_BKObject.AddPlat(t3);

	t3 = New PlatObject;
	t3->LoadFile(L"PLAT", L"../../data/bmp/Plat.bmp");
	t3->Set(1462, 721, 290, 0, 145, 240);
	t3->Init();
	m_BKObject.AddPlat(t3);

	m_pPlayer.Set(130, 350, 10, 87, 25, 36);
	m_pPlayer.Init();
	m_pPlayer.setRendering(2.8f, INVERSE::DEFAULT);
	m_pScroll.Init();
	m_pScroll.setScene5(true);

	m_fDeadScene = New FadeObject;
	m_fDeadScene->Init();
	m_fDeadScene->SetAlpha(0.0f);
	m_fDeadScene->Decrease(0.0f);

	return true;
}
bool GameScene5::Frame()
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
	m_BKObject.Collision(&m_pPlayer);
	if (m_BKObject.isPlatUp())
	{
		m_BKObject.PlatUp();
	}
	for (NPCLIST it = m_NPCList.begin(); it != m_NPCList.end();)
	{
		m_BKObject.Collision(*it);
		(*it)->Process(&m_pPlayer);
		if ((*it)->isDead())
		{
			it = m_NPCList.erase(it);
		}
		else
		{
			it++;
		}
	}
	if (m_fDeadScene)
	{
		m_fDeadScene->Frame();
	}
	m_pPlayer.Frame();
	if (m_pPlayer.getCurrentState() == "Death")
	{
		m_fDeadScene->SetAlpha(255.0f);
	}
	if (m_pPlayer.isDead())
	{
		m_bNextSceneStart = true;
		return false;
	}
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
bool GameScene5::Render()
{
	m_BKObject.Render();
	for (auto it : m_NPCList)
	{
		it->Render();
	}
	if (m_fDeadScene)
	{
		m_fDeadScene->Render();
	}
	m_pPlayer.Render();
	m_pScroll.Render();
	if (m_pFadeObject)
	{
		m_pFadeObject->Render();
	}

	return true;
}
bool GameScene5::Release()
{
	delete m_fDeadScene;
	m_pPlayer.Release();
	m_BKObject.Release();
	for (auto it : m_NPCList)
	{
		it->Release();
	}
	return true;
}
bool GameScene5::inverseSet()
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