#pragma once
#include "TEnemyState.h"
#include "TFsmMgr.h"

class TEnemy : public TObject
{
public:
	TEnemyState*		m_pAction;
	TEnemyState*		m_pActionList[STATE_COUNT];
	DWORD				m_dwCurrentState;
	int					m_iFsmID;
	TFiniteStateMachine* m_pFsm;
public:
	void  SetFSM(int id)
	{
		m_iFsmID = id;
		m_pFsm = I_fsmMgr.GetPtr(id);
	}
public:
	void    Move(tPoint pos);
	bool	Move();
	bool	Frame() { return true; }
	bool	Process(TObject* pTarget);
	DWORD   SetTransition(DWORD dwEvent);
public:
	TEnemy();
	virtual ~TEnemy();
};

