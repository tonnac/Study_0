#include "EnemyBasicState.h"
#include "Enemy.h"

EnemyBasicState::EnemyBasicState(Enemy* pEnemy) : State(pEnemy)
{}

bool EnemyBasicState::Render()
{
	return true;
}

bool EnemyBasicState::Release()
{
	if (m_pEffectObj)
	{
		
		delete m_pEffectObj;
		m_pEffectObj = nullptr;
	}
	return true;
}

EnemyMoveState::EnemyMoveState(Enemy* pEnemy) : EnemyBasicState(pEnemy)
{}
bool EnemyMoveState::Init()
{

}
bool EnemyMoveState::Frame()
{

}

EnemyAttackState::EnemyAttackState(Enemy* pEnemy) : EnemyBasicState(pEnemy)
{}
bool EnemyAttackState::Init()
{

}
bool EnemyAttackState::Frame()
{

}


EnemyHitState::EnemyHitState(Enemy* pEnemy) : EnemyBasicState(pEnemy)
{}
bool EnemyHitState::Init()
{

}
bool EnemyHitState::Frame()
{

}