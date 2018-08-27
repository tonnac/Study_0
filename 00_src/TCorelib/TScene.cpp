#include "TScene.h"
#include "TInput.h"
#include "TSound.h"

void    TScene::SetNpcCount(int iNpc)
{
	if (g_iMaxNpcCount <= iNpc)
	{
		m_iMaxNpcCount = g_iMaxNpcCount;
		return;
	}
	m_iMaxNpcCount = iNpc;
}
bool    TSceneGame::Reset()
{
	m_bNextSceneStart = false;
	for (int iObj = 0; iObj < g_iMaxNpcCount; iObj++)
	{
		m_npcList[iObj].m_bDead = false;
		m_npcList[iObj].Set(
			100 + rand() % 600,
			100 + rand() % 400,
			46, 62, 68, 79);
	}
	return true;
}
bool	TSceneGame::Init()
{
		int iIndexFsm = I_fsmMgr.Load(L"../../data/fsmDefault.txt");
		int iIndexFsm2 = I_fsmMgr.Load(L"../../data/fsmLevel1.txt");

		m_EffectMgr.GameDataLoad(L"../../data/SpriteList.txt");

		m_BackGround.Init();
		m_BackGround.Set(g_rtClient.right / 2,
			g_rtClient.bottom / 2, 0, 0, 800, 600);
		m_BackGround.Load(
			L"../../data/eye.bmp");
		m_Hero.Set(300, 900, 90, 2, 42, 58);
		m_Hero.Load(
			L"../../data/bitmap1.bmp",
			L"../../data/bitmap2.bmp");

		m_npcList.resize(g_iMaxNpcCount);
		for (int iNpc = 0; iNpc < g_iMaxNpcCount; iNpc++)
		{
			m_npcList[iNpc].SetFSM(1 + (rand() % I_fsmMgr.Size()));
			if (m_npcList[iNpc].m_iFsmID == 1)
			{
				m_npcList[iNpc].Set(
					100 + rand() % 300,
					100 + rand() % 200,
					46, 62, 68, 79);
			}
			else
			{
				m_npcList[iNpc].Set(
					100 + rand() % 300,
					100 + rand() % 200,
					115, 62, 37, 35);
			}

			m_npcList[iNpc].Load(
				L"../../data/bitmap1.bmp",
				L"../../data/bitmap2.bmp");
			m_npcList[iNpc].m_bDebugRect = true;
			m_npcList[iNpc].m_fSpeed = 10 + rand() % 200;
			m_npcList[iNpc].m_fAttackRadius = 30 + rand() % 300;
		}
		/*for (int iObj = 0; iObj < g_iMaxNpcCount; iObj++)
		{
			m_npcList[iObj].Set(
				100 + rand() % 600,
				100 + rand() % 400,
				46, 62, 68, 79);
			m_npcList[iObj].Load(
				L"../../data/bitmap1.bmp",
				L"../../data/bitmap2.bmp");
		}*/
		return true;
}
bool	TSceneGame::GetNpcDead(int iNpc)
{
	return m_npcList[iNpc].m_bDead;
}
void	TSceneGame::SetNpcDead(int iNpc, bool bDead)
{
	m_npcList[iNpc].m_bDead = bDead;
}
RECT    TSceneGame::GetCollider(int inpc)
{	
	return m_npcList[inpc].m_rtCollision;
}
bool	TSceneGame::Frame()
	{
		if (I_Input.Key('0') == KEY_PUSH)
		{
			m_Hero.m_bDebugRect = !m_Hero.m_bDebugRect;
			for (int iObj = 0; iObj < m_iMaxNpcCount; iObj++)
			{
				m_npcList[iObj].m_bDebugRect =
					!m_npcList[iObj].m_bDebugRect;
			}
		}

		m_BackGround.Frame();
		m_Hero.Frame();
		for (int inpc = 0; inpc < m_iMaxNpcCount; inpc++)
		{
			if (!m_npcList[inpc].m_bDead)
			{
				m_npcList[inpc].Frame();
				m_npcList[inpc].Process(&m_Hero);
			}
		}
		
		m_EffectMgr.Frame();

		for (int inpc = 0; inpc < g_iMaxNpcCount; inpc++)
		{
			if (GetNpcDead(inpc) == false)
			{
				if (m_EffectMgr.IsCollision(
					GetCollider(inpc)))
				{
					SetNpcDead(inpc, true);
					TSound::Get()->PlayEffect(3);
				}
			}
		}

		for (int inpc = 0; inpc < m_iMaxNpcCount; inpc++)
		{
			if (TCollision::SphereInSphere(
				m_npcList[inpc].m_rtCollision,
				m_Hero.m_rtCollision))
			{
				m_Hero.m_bDead = true;
			}
		}
		bool bChangeScene = true;
		for (int inpc = 0; inpc < m_iMaxNpcCount; inpc++)
		{		
			if(m_npcList[inpc].m_bDead==false)
			{
				bChangeScene = false;
			}
		}
		if (bChangeScene==true)
		{
			m_bNextSceneStart = true;
		}		
		return true;
}
bool	TSceneGame::Render() {
		//m_BackGround.Draw(LRTB_ROTATION);
		//m_BackGround.DrawColorKey(RGB(255,0,0));
		m_BackGround.Render();
		m_Hero.Render();
		for (int inpc = 0; inpc < m_iMaxNpcCount; inpc++)
		{
			if (!m_npcList[inpc].m_bDead)
			{
				m_npcList[inpc].Render();
			}
		}
		m_EffectMgr.Render();
		return true;
	}
bool	TSceneGame::Release() {
		m_BackGround.Release();
		m_Hero.Release();
		m_EffectMgr.Release();
		for (int iObj = 0; iObj < m_iMaxNpcCount; iObj++)
		{
			m_npcList[iObj].Release();
		}
		return true;
	}
TSceneGame::TSceneGame()
{
	m_iSceneID = SCENE_PLAYLEVEL;
}
TSceneGame::~TSceneGame()
{
}
