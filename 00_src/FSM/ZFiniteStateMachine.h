#pragma once
#include "Std.h"

enum EnumyActionState
{
	STATE_STAND = 0,
	STATE_MOVE,
	STATE_ATTACK,
	STATE_COUNT
};
enum EnumyEvent
{
	EVENT_PATROL= 0,
	EVENT_FINDTARGET,
	EVENT_LOSTTARGET,
	EVENT_STOPWALK,
	EVENT_COUNT
};
class ZFiniteState
{
private:
	// event -> output
	std::map<DWORD, DWORD> m_mapOutState;
public:
	void AddTransition(DWORD dwEvent, DWORD dwOutput)
	{
		m_mapOutState[dwEvent] = dwOutput;
	}
	DWORD GetState(DWORD dwEvent)
	{
		return m_mapOutState[dwEvent];
	}
public:
	ZFiniteState() 
	{
		m_mapOutState.clear();
	};
	virtual ~ZFiniteState() {};
};

class ZFiniteStateMachine
{
	std::map<DWORD, ZFiniteState*> m_mapState;
	using ITER = std::map<DWORD, ZFiniteState*>::iterator;
public:
	DWORD StateTransition(DWORD dwCurrentState, DWORD dwEvent);
	void AddStateTransition(
		DWORD dwState, 
		DWORD dwEvent, 
		DWORD dwOutState);
public:
	ZFiniteStateMachine();
	virtual ~ZFiniteStateMachine();
};

