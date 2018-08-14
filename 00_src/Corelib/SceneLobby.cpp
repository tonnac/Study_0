#include "Scene.h"
#include "Input.h"
bool SceneLobby::Init()
{
	m_bNextSceneStart = false;
	m_BackGround.LoadFile(L"../../data/bk.bmp");
	m_BackGround.Set(g_rtClient.right / 2,g_rtClient.bottom / 2 , 0, 0, 800, 600);
	m_BackGround.Init();

	m_btnStart.LoadFile(L"../../data/main_start_nor.bmp", nullptr, 0);
	m_btnStart.LoadFile(L"../../data/main_start_dis.bmp", nullptr, 1);
	m_btnStart.LoadFile(L"../../data/main_start_sel.bmp", nullptr, 2);
	m_btnStart.LoadFile(L"../../data/main_start_sel.bmp", nullptr ,3);
	m_btnStart.Set(g_rtClient.right / 2, g_rtClient.bottom / 2, 0, 0, 334, 82);
	m_btnStart.Init();
	return true;
}
bool SceneLobby::Frame()
{
	m_btnStart.Frame();
	if (I_KInput.getMouse(VK_LBUTTON) == KEY_UP && Collision::RectInPt(m_btnStart.m_rtCollision, I_KInput.m_MousePos))
	{
		m_bNextSceneStart = true;
	}
	m_BackGround.Frame();
	return true;
}
bool SceneLobby::Render()
{
	m_BackGround.Render();
	m_btnStart.Render();
	return true;
}
bool SceneLobby::Release()
{
	m_btnStart.Release();
	m_BackGround.Release();
	return true;
}

SceneLobby::SceneLobby() 
{
	m_iSceneID = SCENE_LOBBY;
}
SceneLobby::~SceneLobby() 
{
}