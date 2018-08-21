#pragma once
#include "SpriteMgr.h"
#include "CharacterObject.h"

class State
{
public:
	State(CharacterObject*);
public:
	virtual bool		Init		() = 0;
	virtual bool		Frame		() = 0;
	virtual bool		Render		();
	virtual bool		Release		();
public:
	void				setSprite	(T_STR, T_STR);
public:
	void * operator new(size_t sz, const char* FileName, int iLine);
	void operator delete(void * p);
protected:
	CharacterObject *	m_pCharObj;
	Sprite *			m_pSprite;
	FloatPoint*			m_CenterPos;
	RECT*				m_rtDraw;
};
//	FloatPoint*			m_DrawPos;
//	RECT*				m_rtCollision;
//m_DrawPos(pObject->getDrawPos()), m_rtCollision(pObject->getCollisionRt()),
