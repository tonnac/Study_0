#pragma once
#include "Object.h"

class Scroll
{
public:
	Scroll(Object * object, Object * pBkObj);
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
	Object*				m_pPlayer;
	Object*				m_pBkObj;
	RECT*				m_PlayerCollisionRt;
	RECT*				m_BkRtDraw;
	FloatPoint			m_CenterPos;
	RECT				m_rtCollision;
};