#include "Enemy.h"


Enemy::Enemy()
{
	EnemyBasicState * state = New EnemyMoveState(this);
	state = New EnemyAttackState(this);
	state = New EnemyHitState(this);
	state = New EnemyChaseState(this);
	m_HP = 50;
	m_Damage = 8;
}

bool Enemy::Init()
{
	for (auto it : m_pStateList)
	{
		it.second->Init();
	}
	m_pCurrentState = m_pStateList["Move"];
	m_sCurrestState = "Move";
	Object::Init();
	return true;
}
bool Enemy::Frame()
{
	return true;
}
bool Enemy::Render()
{
	Object::Render();
	int prev = SetROP2(g_hOffScreenDC, R2_MASKPEN);

	Rectangle(g_hOffScreenDC, m_rtArea.left, m_rtArea.top, m_rtArea.right, m_rtArea.bottom);
	Rectangle(g_hOffScreenDC, m_rtSight.left, m_rtSight.top, m_rtSight.right, m_rtSight.bottom);
	Rectangle(g_hOffScreenDC, m_rtAttackRange.left, m_rtAttackRange.top, m_rtAttackRange.right, m_rtAttackRange.bottom);

	SetROP2(g_hOffScreenDC, prev);
	return true;
}
FloatRect* Enemy::getArea()
{
	return &m_rtArea;
}
FloatRect* Enemy::getSight()
{
	return &m_rtSight;
}
FloatRect* Enemy::getAttackRange()
{
	return &m_rtAttackRange;
}
void Enemy::setArea(const FloatRect& area)
{
	m_rtArea = area;
}
void Enemy::setSight(const FloatRect& sight)
{
	m_rtSight = sight;
}
void Enemy::setAttackRange(const FloatRect& arange)
{
	m_rtAttackRange = arange;
}
bool Enemy::MoveScrollObj(const LONG& size)
{
	m_fScroll = (g_fPerSecFrame * g_fSpeed);
	if (size < 0)
	{
		m_rtArea.left			+= m_fScroll;
		m_rtArea.right			+= m_fScroll;
		m_rtSight.left			+= m_fScroll;
		m_rtSight.right			+= m_fScroll;
		m_rtAttackRange.left	+= m_fScroll;
		m_rtAttackRange.right	+= m_fScroll;
	}
	else
	{
		m_rtArea.left			-= m_fScroll;
		m_rtArea.right			-= m_fScroll;
		m_rtSight.left			-= m_fScroll;
		m_rtSight.right			-= m_fScroll;
		m_rtAttackRange.left	-= m_fScroll;
		m_rtAttackRange.right	-= m_fScroll;
	}
	return true;
}
bool Enemy::isFallState()
{
	return false;
}
bool Enemy::Process(Player * pObject)
{
	Object::Frame();
	m_pCurrentState->Process(pObject);
	return true;
}
Enemy::~Enemy()
{
	for (auto it : m_pStateList)
	{
		it.second->Release();
		delete it.second;
		m_pStateList.erase(it.first);
	}
	m_pStateList.clear();
}
