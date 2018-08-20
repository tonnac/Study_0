#pragma once
#include "Scene.h"
#include "FadeObject.h"

class GameScene : public Scene
{
public:
	GameScene();
public:
	bool		Init		() override;
	bool		Frame		() override;
	bool		Render		() override;
	bool		Release		() override;
	bool		inverseSet	() override;
private:
	Player		m_pPlayer;
	Scroll		m_pScroll;
	FadeObject* m_pFadeObject;
};

class GameScene2 : public Scene
{
public:
	GameScene2();
public:
	bool		Init		() override;
	bool		Frame		() override;
	bool		Render		() override;
	bool		Release		() override;
	bool		inverseSet	() override;
private:
	Player		m_pPlayer;
	Scroll		m_pScroll;
	FadeObject* m_pFadeObject;
};