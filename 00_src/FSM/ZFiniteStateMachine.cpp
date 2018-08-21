#include "ZFiniteStateMachine.h"

void ZFiniteStateMachine::AddStateTransition(DWORD dwState, DWORD dwEvent, DWORD dwOutState)
{
	ITER iter;
	iter = m_mapState.find(dwState);
	ZFiniteState * pState = nullptr;
	if (iter != m_mapState.end())
	{
		pState = iter->second;
	}
	else
	{
		pState = new ZFiniteState;
		m_mapState[dwState] = pState;
	}
	pState->AddTransition(dwEvent, dwOutState);

}
DWORD ZFiniteStateMachine::StateTransition(DWORD dwCurrentState, DWORD dwEvent)
{
	return m_mapState[dwCurrentState]->GetState(dwEvent);
}
ZFiniteStateMachine::ZFiniteStateMachine()
{
	//				������ -> �̺�Ʈ -> ��»���
	AddStateTransition(
		STATE_STAND, 
		EVENT_PATROL, 
		STATE_MOVE);
	AddStateTransition(
		STATE_STAND,
		EVENT_FINDTARGET,
		STATE_ATTACK);
}


ZFiniteStateMachine::~ZFiniteStateMachine()
{
}
