#pragma once
#include "Core.h"
#include "KbkObject.h"
#include "NPCObj.h"
#include "Button.h"


const int g_iMaxLevel = 10;
const int g_iMaxNpcCount = 100;

class Scene
{
public:
	int						m_iSceneID;
	KbkObject				m_BackGround;
	bool					m_bNextSceneStart;
	int						m_iMaxNpcCount;
public:
	virtual	bool			Init() { return true; }
	virtual	bool			Frame() { return true; }
	virtual	bool			Render() { return true; }
	virtual bool			Release() { return true; }
	virtual bool			isDead() { return m_iSceneID; }
	virtual bool			Reset() { return true; }
public:
	Scene();
	virtual ~Scene();
};

class SceneLobby : public Scene
{
public:
	Button					m_btnStart;
public:
	virtual	bool			Init() override;
	virtual	bool			Frame() override;
	virtual	bool			Render() override;
	virtual bool			Release() override;
	virtual bool			Reset() { return true; }
//	virtual bool			isDead();
public:
	SceneLobby();
	virtual ~SceneLobby();
};

class SceneGame : public Scene
{public:
	std::vector<NPCObj>		m_npcList;
	KObject					m_Hero;
public:
	bool					Init() override;
	bool					Frame() override;
	bool					Render() override;
	bool					Release() override;
	virtual bool			Reset() override;
public:
	SceneGame() {}
	virtual ~SceneGame() {}
};

