#pragma once
#include "TStd.h"

enum TEnemyActionState
{
	STATE_STAND = 0,
	STATE_MOVE,
	STATE_ATTACK,
	STATE_COUNT,
};
enum TEnemyEventState
{
	EVENT_PATROL = 0,
	EVENT_FINDTARGET,
	EVENT_LOSTTARGET,
	EVENT_STOPWALK,
	EVENT_COUNT,
};

class TFiniteState
{
	// event -> output
	std::map<DWORD, DWORD>  m_mapOutState;
public:

	DWORD   m_dwState;
public:
	void AddEventTransition(DWORD dwEvent, DWORD dwOutput)
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
	TFiniteState() {};
	virtual ~TFiniteState() {};
};

class TFiniteStateMachine
{
	std::map<DWORD, TFiniteState*>  m_mapState;
public:
	T_STR   m_szName;
public:
	bool   Load(T_STR szLoadFile);
	void AddStateTransition(
		DWORD dwState, 
		DWORD dwEvent, 
		DWORD dwOutState);
	DWORD StateTransition(
		DWORD dwState,
		DWORD dwEvent);
public:
	int    GetIndex(T_STR szState);
public:
	TFiniteStateMachine();
	virtual ~TFiniteStateMachine();
};

