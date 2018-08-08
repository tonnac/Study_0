#include "EndScene.h"
#include "Input.h"
bool EndScene::Init()
{
	m_bNextSceneStart = false;
	m_BackGround.LoadFile(L"../../data/RAINBOW.bmp");
	m_BackGround.Set(g_rtClient.right / 2, g_rtClient.bottom / 2, 0, 0, 800, 600);
	m_BackGround.Init();

	m_btnStart.LoadFile(L"../../data/end.bmp");
	m_btnStart.Set(g_rtClient.right / 2, g_rtClient.bottom / 2, 0, 0, 100, 50);
	m_btnStart.Init();
	return true;
}
bool EndScene::Frame()
{
	m_btnStart.Frame();
	if (I_KInput.getMouse(VK_LBUTTON) && Collision::RectInPt(m_btnStart.m_rtCollision, I_KInput.m_MousePos))
	{
		DestroyWindow(g_hWnd);
	}
	m_BackGround.Frame();
	return true;
}
bool EndScene::Render()
{
	m_BackGround.Render();
	m_btnStart.Render();
	return true;
}
bool EndScene::Release()
{
	m_btnStart.Release();
	m_BackGround.Release();
	return true;
}

EndScene::EndScene()
{
	m_iSceneID = 2;
}
EndScene::~EndScene()
{
}