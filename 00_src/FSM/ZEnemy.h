#pragma once
#include "ZEnemyState.h"
#include "ZFiniteStateMachine.h"
class ZEnemyState;

class ZEnemy : public KObject
{
	ZFiniteStateMachine m_fsm;
	ZEnemyState *		m_pAction;
	ZEnemyState *		m_pActionList[STATE_COUNT];
	DWORD				m_dwCurrentState;
public:
	bool			Frame() override;
	bool			Process(KObject * pTarget);
	DWORD			SetTransition(DWORD dwEvent);
public:
	ZEnemy();
	virtual ~ZEnemy();
};

