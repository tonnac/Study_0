#pragma once
#include "TNpcObj.h"

typedef std::vector<RECT>  RECT_ARRAY;

class TEffectObj : public TNpcObj
{
public:
	int			m_iSpriteIndex;
	int			m_iCurrentRect;
	float		m_fSpriteTime;
	float		m_fOffset;
	float		m_fLifeTime;
public:
	bool Frame();
public:
	TEffectObj();
	virtual ~TEffectObj();
};

class TEffectMgr
{
public:
	std::vector<TEffectObj>   m_EffectObj;
	std::vector<RECT_ARRAY>  m_rtSpriteList;
	float m_fAngle;
public:
	bool GameDataLoad(const TCHAR* pszLoad);
	void AddEffect(POINT pos);
	bool IsCollision(RECT rt);
	bool Frame();
	bool Render();
	bool Release();
public:
	TEffectMgr();
	virtual ~TEffectMgr();
};