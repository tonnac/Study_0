#include "KahoAttack.h"

bool KahoAttack1::Init()
{
	m_pEffectSprite = S_SpriteMgr.LoadSprite(L"Kaho", L"Leaf1");
	m_pEffectSprite->setIndex(0);
	m_pEffectSprite->setDivideTime(0.9f);
	Object::Init();
	return true;
}
bool KahoAttack1::Frame()
{
	EffectObj::Frame();
	if (m_pEffectSprite->getIndex() < 4)
	{
		m_rtCollision.left = 0;
		m_rtCollision.right = 0;
		m_rtCollision.bottom = 0;
		m_rtCollision.top = 0;
	}
	return true;
}

bool KahoAttack2::Init()
{
	m_pEffectSprite = S_SpriteMgr.LoadSprite(L"Kaho", L"Leaf2");
	m_pEffectSprite->setIndex(0);
	m_pEffectSprite->setDivideTime(1.0f);
	Object::Init();
	return true;
}
bool KahoAttack2::Frame()
{
	EffectObj::Frame();
	if (m_pEffectSprite->getIndex() < 4)
	{
		m_rtCollision.left = 0;
		m_rtCollision.right = 0;
		m_rtCollision.bottom = 0;
		m_rtCollision.top = 0;
	}
	return true;
}

bool KahoAttack3::Init()
{
	m_pEffectSprite = S_SpriteMgr.LoadSprite(L"Kaho", L"Leaf3");
	m_pEffectSprite->setIndex(0);
	m_pEffectSprite->setDivideTime(1.2f);
	Object::Init();
	return true;
}
bool KahoAttack3::Frame()
{
	EffectObj::Frame();
	if (m_pEffectSprite->getIndex() < 5)
	{
		m_rtCollision.left = 0;
		m_rtCollision.right = 0;
		m_rtCollision.bottom = 0;
		m_rtCollision.top = 0;
	}
	return true;
}


bool KahoAirAttack::Init()
{
	m_pEffectSprite = S_SpriteMgr.LoadSprite(L"Kaho", L"AirLeaf");
	m_pEffectSprite->setIndex(0);
	m_pEffectSprite->setDivideTime(0.75f);
	Object::Init();
	return true;
}
bool KahoAirAttack::Frame()
{
	EffectObj::Frame();
	if (m_pEffectSprite->getIndex() < 2)
	{
		m_rtCollision.left = 0;
		m_rtCollision.right = 0;
		m_rtCollision.bottom = 0;
		m_rtCollision.top = 0;
	}
	return true;
}