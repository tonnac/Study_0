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
	DWORD	m_dwState;
public:
	void AddTransition(DWORD dwEvent, DWORD dwOutput)
	{
		m_mapOutState[dwEvent] = dwOutput;
	}
	DWORD GetState(DWORD dwEvent)
	{
		std::map<DWORD, DWORD>::iterator iter;
		iter = m_mapOutState.find(dwEvent);
		if (iter != m_mapOutState.end())
		{
			return m_mapOutState[dwEvent];
		}
		return m_dwState;
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
	T_STR	m_szName;
public:
	bool	LoadFile(T_STR);
	int		GetIndex(T_STR szState);
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

