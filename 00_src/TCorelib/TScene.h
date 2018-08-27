#pragma once
#include "TBkObj.h"
#include "TEnemy.h"
#include "THeroObj.h"
#include "TButton.h"
#include "TEffectObj.h"

const int g_iMaxLevel = 10;
const int g_iMaxNpcCount = 100;

enum  TGameScene {
	SCENE_LOBBY=0,
	SCENE_PLAYLEVEL,
	SCENE_END,
};
class TScene
{
public:
	TEffectMgr	m_EffectMgr;
	int		m_iSceneID;
	TBkObj  m_BackGround;
	bool	m_bNextSceneStart;
	int		m_iMaxNpcCount;
public:
	virtual bool    FadeOut() { return true; }
	virtual bool    FadeIn() { return true; }
	virtual bool	Init() {return true;};
	virtual bool	Frame() { return true; };
	virtual bool	Render() { return true; };
	virtual bool	Release() { return true; };
	virtual bool    Reset() { return true; };
	virtual bool	IsDead() { return false; };
	virtual bool	GetNpcDead(int iNpc) { return false; };
	virtual void	SetNpcDead(int iNpc, bool bDead=true) {};
	virtual RECT    GetCollider(int inpc) { 
		RECT rt = { 0, 0, 0, 0 }; 
		return rt; 
	}
	virtual void    SetNpcCount(int iNpc);
public:
	TScene() { 
		m_bNextSceneStart = false;
		m_iMaxNpcCount = 10;
	}
	virtual ~TScene() {}
};
class TSceneLobby : public TScene
{
public:
	TButton m_btnStart;
	
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
	bool    Reset() { return true; };
	bool	IsDead() { return m_btnStart.m_bDead; };
	bool    FadeOut() { 
		m_BackGround.FadeOut();
		return true; 
	}
	bool    FadeIn() { return true; }
public:
	TSceneLobby();
	virtual ~TSceneLobby();
};
class TSceneEnd : public TScene
{
public:
	TButton m_btnStart;

public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
	bool    Reset() { return true; };
	bool	IsDead() { return m_btnStart.m_bDead; };
public:
	TSceneEnd();
	virtual ~TSceneEnd();
};
class TSceneGame : public TScene
{
public:	
	THeroObj m_Hero;
	std::vector<TEnemy> m_npcList;	
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
	bool    Reset();
	bool	GetNpcDead(int iNpc);
	void	SetNpcDead(int iNpc, bool bDead);
	RECT    GetCollider(int inpc);
public:
	TSceneGame();
	virtual ~TSceneGame();
};

