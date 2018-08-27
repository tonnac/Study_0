#include "TScene.h"
#include "TInput.h"

bool	TSceneEnd::Init()
{
	m_bNextSceneStart = false;

	m_BackGround.Init();
	m_BackGround.Set(g_rtClient.right / 2,
		g_rtClient.bottom / 2, 0, 0, 800, 600);
	m_BackGround.Load(
		L"../../data/RAINBOW.bmp");

	m_btnStart.Init();
	m_btnStart.Set(
		g_rtClient.right / 2,
		g_rtClient.bottom / 2,
		0, 0, 100, 50);
	m_btnStart.Load(
		L"../../data/end.bmp");


	return true;
};
bool	TSceneEnd::Frame()
{
	m_BackGround.Frame();
	//for (int inpc = 0; inpc < g_iMaxNpcCount; inpc++)
	{
		if (I_Input.Key(VK_LBUTTON) &&
			TCollision::RectInPt(
				m_btnStart.m_rtCollision,
				I_Input.m_MousePos))
		{
			DestroyWindow(g_hWnd);
		}
	}
	m_btnStart.Frame();
	return true;
};
bool	TSceneEnd::Render()
{
	m_BackGround.Render();
	m_btnStart.Render();
	return true;
};
bool	TSceneEnd::Release()
{
	m_BackGround.Release();
	m_btnStart.Release();
	return true;
};
TSceneEnd::TSceneEnd()
{
	m_iSceneID = SCENE_END;
}
TSceneEnd::~TSceneEnd()
{}