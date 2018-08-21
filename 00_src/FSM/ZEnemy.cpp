#include "ZEnemy.h"
#include "ZMoveAction.h"
#include "ZAttackAction.h"
#include "ZStandAction.h"

bool ZEnemy::Frame()
{
	return true;
}
bool ZEnemy::Process(KObject * pTarget)
{
	m_pAction->Process(pTarget);
	return true;
}
DWORD ZEnemy::SetTransition(DWORD dwEvent)
{
	m_dwCurrentState = m_fsm.StateTransition(m_dwCurrentState, dwEvent);
	m_pAction = m_pActionList[m_dwCurrentState];
	return m_dwCurrentState;
}

ZEnemy::ZEnemy()
{
	m_pActionList[STATE_STAND] = new ZStandAction(this);
	m_pActionList[STATE_MOVE] = new ZMoveAction(this);
	m_pActionList[STATE_ATTACK] = new ZAttackAction(this);
	m_pAction = m_pActionList[STATE_STAND];
	m_dwCurrentState = STATE_STAND;
}

ZEnemy::~ZEnemy()
{
	delete m_pActionList[STATE_STAND];
	delete m_pActionList[STATE_MOVE];
	delete m_pActionList[STATE_ATTACK];
}
