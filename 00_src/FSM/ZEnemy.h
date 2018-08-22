#pragma once
#include "ZEnemyState.h"
#include "ZFiniteStateMachine.h"
#include "ZFsmMgr.h"
class ZEnemyState;

class ZEnemy : public Object
{
	ZEnemyState *			m_pAction;
	ZEnemyState *			m_pActionList[STATE_COUNT];
	DWORD					m_dwCurrentState;
	int						m_FsmID;
	ZFiniteStateMachine*	m_pFsm;
public:
	bool					Frame() override;
	bool					Process(Object * pTarget);
	DWORD					SetTransition(DWORD dwEvent);
public:
	void					SetFsm(int id)
	{
		m_FsmID = id;
		m_pFsm = I_ZFsmMgr.getPtr(id);
	}
public:
	ZEnemy();
	virtual ~ZEnemy();
};

