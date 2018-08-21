#pragma once
#include "Enemy.h"


class Scroll
{
public:
	Scroll(Object * object, Object * pBkObj, std::list<Enemy*>* npcVector = nullptr);
public:
	bool				Init		();
	bool				Frame		();
	bool				Render		();
	bool				Release		();
	bool				MoveCamera	(const LONG& size);
private:
	bool				Collision	(const RECT&);
private:
	std::array<INT,2>	m_nInitValue;
	std::list<Enemy*>*	m_npclist;
	Object*				m_pPlayer;
	Object*				m_pBkObj;
	RECT*				m_PlayerCollisionRt;
	RECT*				m_BkRtDraw;
	FloatPoint			m_CenterPos;
	RECT				m_rtCollision;
};