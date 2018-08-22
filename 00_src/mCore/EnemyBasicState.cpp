#include "EnemyBasicState.h"
#include "Enemy.h"
#include "Player.h"

EnemyBasicState::EnemyBasicState(Enemy* pEnemy) : State(pEnemy), m_pEnemy(pEnemy)
{
	m_CenterPos = m_pEnemy->getCenterPos();
	m_rtDraw = m_pEnemy->getrtDraw();
	m_rtArea = m_pEnemy->getArea();
	m_rtSight = m_pEnemy->getSight();
	m_rtAttackRange = m_pEnemy->getAttackRange();
	pEnemy->setSpeed(120.0f);
}
bool EnemyBasicState::Render()
{
	return true;
}
bool EnemyBasicState::Release()
{
	return true;
}

EnemyMoveState::EnemyMoveState(Enemy* pEnemy) : EnemyBasicState(pEnemy)
{
	pEnemy->addState(std::string("Move"), this);
}
bool EnemyMoveState::Init()
{
	setSprite(L"Monkey", L"Labeled");
	m_pSprite->setDivideTime(1.0f);
	return true;
}
bool EnemyMoveState::Process(Player * pPlayer)
{
	RECT playerEffectRT = pPlayer->getEffectObj();
	const RECT collisionRT = *m_pEnemy->getCollisionRt();
	const RECT playerRT = *pPlayer->getCollisionRt();
	FLOAT fSpeed = m_pEnemy->getSpeed();
	INT iDir = m_pEnemy->getDir();
	m_CenterPos->x += iDir * g_fPerSecFrame * fSpeed;
	m_CenterPos->y += g_fPerSecFrame * 10.0f;

	if (iDir == -1)
	{
		m_rtSight->left = collisionRT.left - 100.0f;
		m_rtSight->top = collisionRT.top - 150.0f;
		m_rtSight->right = m_CenterPos->x;
		m_rtSight->bottom = collisionRT.bottom;

		m_rtAttackRange->left = collisionRT.left - 10.0f;
		m_rtAttackRange->top = collisionRT.top;
		m_rtAttackRange->right = collisionRT.left;
		m_rtAttackRange->bottom = collisionRT.bottom;
	}
	else
	{
		m_rtSight->left = m_CenterPos->x;
		m_rtSight->top = collisionRT.top - 150.0f;
		m_rtSight->right = collisionRT.right + 100.0f;
		m_rtSight->bottom = collisionRT.bottom;

		m_rtAttackRange->left = collisionRT.right + 10.0f;
		m_rtAttackRange->top = collisionRT.top;
		m_rtAttackRange->right = collisionRT.right;
		m_rtAttackRange->bottom = collisionRT.bottom;
	}
	if (CollisionClass::RectInRect(playerEffectRT, collisionRT))
	{
		m_pSprite->setIndex(0);
		m_pEnemy->setHP(pPlayer->getDamage());
		if (m_pEnemy->isDead())
		{
			m_pEnemy->Release();
			return true;
		}
		m_pEnemy->setTransition(E_EVENT::BEATTACKED);
		return true;
	}
	if (!m_pSprite->Frame())
	{
		m_pSprite->setIndex(0);
	}
	if (CollisionClass::RectInRect(playerRT, *m_rtSight))
	{
		m_pSprite->setIndex(0);
		m_pEnemy->setSpeed(110.0f);
		m_pEnemy->setTransition(E_EVENT::FINDTARGET);
		return true;
	}
	if (m_rtArea->right <= m_rtSight->right || m_rtArea->left >= m_rtSight->left)
	{
		if (m_pEnemy->getDir() == 1)
		{
			m_CenterPos->x += -30;
			m_pEnemy->setRendering(2.8f, INVERSE::LR_ROTATION);
		}
		else
		{
			m_CenterPos->x += 30;
			m_pEnemy->setRendering(2.8f, INVERSE::DEFAULT);
		}
		m_pEnemy->setDir(-1);
	}
	*m_rtDraw = m_pSprite->getSpriteRt();
	return true;
}

EnemyChaseState::EnemyChaseState(Enemy* pEnemy) : EnemyBasicState(pEnemy)
{
	pEnemy->addState(std::string("Chase"), this);
}
bool EnemyChaseState::Init()
{
	setSprite(L"Monkey", L"Labeled");
	m_pSprite->setDivideTime(1.0f);
	return true;
}
bool EnemyChaseState::Process(Player * pPlayer)
{
	RECT playerEffectRT = pPlayer->getEffectObj();
	const RECT collisionRT = *m_pEnemy->getCollisionRt();
	const RECT playerRT = *pPlayer->getCollisionRt();
	FLOAT fSpeed = m_pEnemy->getSpeed();
	INT iDir = m_pEnemy->getDir();
	m_CenterPos->x += iDir * g_fPerSecFrame * fSpeed;
	m_CenterPos->y += g_fPerSecFrame * 10.0f;

	if (iDir == -1)
	{
		m_rtSight->left = collisionRT.left - 100.0f;
		m_rtSight->top = collisionRT.top - 150.0f;
		m_rtSight->right = m_CenterPos->x;
		m_rtSight->bottom = collisionRT.bottom;

		m_rtAttackRange->left = collisionRT.left - 5.0f;
		m_rtAttackRange->top = collisionRT.top;
		m_rtAttackRange->right = collisionRT.left;
		m_rtAttackRange->bottom = collisionRT.bottom;
	}
	else
	{
		m_rtSight->left = collisionRT.right + 100.0f;
		m_rtSight->top = collisionRT.top - 150.0f;
		m_rtSight->right = m_CenterPos->x;
		m_rtSight->bottom = collisionRT.bottom;

		m_rtAttackRange->left = collisionRT.right + 5.0f;
		m_rtAttackRange->top = collisionRT.top;
		m_rtAttackRange->right = collisionRT.right;
		m_rtAttackRange->bottom = collisionRT.bottom;
	}

	if (!m_pSprite->Frame())
	{
		m_pSprite->setIndex(0);
	}
	if (CollisionClass::RectInRect(playerRT, *m_rtAttackRange))
	{
		m_pSprite->setIndex(0);
		m_pEnemy->setTransition(E_EVENT::INATTACKRANGE);
		return true;
	}
	if (CollisionClass::RectInRect(playerEffectRT, collisionRT))
	{
		m_pSprite->setIndex(0);
		m_pEnemy->setHP(pPlayer->getDamage());
		if (m_pEnemy->isDead())
		{
			m_pEnemy->Release();
			return true;
		}
		m_pEnemy->setTransition(E_EVENT::BEATTACKED);
		return true;
	}
	if (CollisionClass::RectInRect(playerRT, *m_rtArea))
	{
		if (m_pEnemy->getDir() == 1 && collisionRT.left > playerRT.right)
		{
			m_pEnemy->setDir(-1);
			m_pEnemy->setRendering(2.8f, INVERSE::LR_ROTATION);
			return true;
		}
		if (m_pEnemy->getDir() == -1 && collisionRT.right < playerRT.left)
		{
			m_pEnemy->setDir(-1);
			m_pEnemy->setRendering(2.8f, INVERSE::DEFAULT);
			return true;
		}
	}
	if (!CollisionClass::RectInRect(playerRT, *m_rtArea))
	{
		m_pSprite->setIndex(0);
		m_pEnemy->setTransition(E_EVENT::LOSTTARGET);
		return true;
	}
	*m_rtDraw = m_pSprite->getSpriteRt();
	return true;
}

EnemyAttackState::EnemyAttackState(Enemy* pEnemy) : EnemyBasicState(pEnemy)
{
	pEnemy->addState(std::string("Attack"), this);
}
bool EnemyAttackState::Init()
{
	setSprite(L"Monkey", L"Attack");
	m_pSprite->setDivideTime(1.7f);
	return true;
}
bool EnemyAttackState::Process(Player * pPlayer)
{
	const RECT collisionRT = *m_pEnemy->getCollisionRt();
	RECT playerEffectRT = pPlayer->getEffectObj();
	m_CenterPos->y += g_fPerSecFrame * 10.0f;
	if (CollisionClass::RectInRect(playerEffectRT, collisionRT))
	{
		m_pSprite->setIndex(0);
		m_pEnemy->setHP(pPlayer->getDamage());
		if (m_pEnemy->isDead())
		{
			m_pEnemy->Release();
			return true;
		}
		m_pEnemy->setTransition(E_EVENT::BEATTACKED);
		return true;
	}
	if (!m_pSprite->Frame())
	{
		m_pSprite->setIndex(0);
		if (!CollisionClass::RectInRect(*pPlayer->getCollisionRt(), *m_rtAttackRange))
		{
			m_pEnemy->setTransition(E_EVENT::OUTATTACKRANGE);
			return true;
		}
	}
	*m_rtDraw = m_pSprite->getSpriteRt();
	return true;
}

EnemyHitState::EnemyHitState(Enemy* pEnemy) : EnemyBasicState(pEnemy)
{
	pEnemy->addState(std::string("Hit"), this);
}
bool EnemyHitState::Init()
{
	setSprite(L"Monkey", L"Hit");
	m_pSprite->setDivideTime(0.5f);
	return true;
}
bool EnemyHitState::Process(Player * pPlayer)
{
	if (!m_pSprite->Frame())
	{
		m_pSprite->setIndex(0);
		m_pEnemy->setTransition(E_EVENT::NOHIT);
		return true;
	}
	*m_rtDraw = m_pSprite->getSpriteRt();
	return true;
}
