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
	pState->m_dwState = dwState;
	pState->AddTransition(dwEvent, dwOutState);

}
DWORD ZFiniteStateMachine::StateTransition(DWORD dwCurrentState, DWORD dwEvent)
{
	ITER it = m_mapState.find(dwCurrentState);
	if (it != m_mapState.end())
	{
		return m_mapState[dwCurrentState]->GetState(dwEvent);
	}
	return dwCurrentState;
}
int ZFiniteStateMachine::GetIndex(T_STR szState)
{
//	for (int iIn = 0; iIn < STATE_COUNT; ++iIn)
	{
		if (_tcscmp(szState.c_str(), _T("STATE_STAND")) == 0)
		{
			return 0;
		}
		if (_tcscmp(szState.c_str(), _T("STATE_MOVE")) == 0)
		{
			return 1;
		}
		if (_tcscmp(szState.c_str(), _T("STATE_ATTACK")) == 0)
		{
			return 2;
		}

		if (_tcscmp(szState.c_str(), _T("EVENT_PATROL")) == 0)
		{
			return 0;
		}
		if (_tcscmp(szState.c_str(), _T("EVENT_FINDTARGET")) == 0)
		{
			return 1;
		}
		if (_tcscmp(szState.c_str(), _T("EVENT_LOSTTARGET")) == 0)
		{
			return 2;
		}
		if (_tcscmp(szState.c_str(), _T("EVENT_STOPWALK")) == 0)
		{
			return 3;
		}
	}
	return -1;
}
bool ZFiniteStateMachine::LoadFile(T_STR szLoadFile)
{
	FILE * fp;
	_wfopen_s(&fp, szLoadFile.c_str(), _T("rt"));
	assert(fp != nullptr);

	TCHAR pBuffer[256] = { 0, };
	TCHAR pTemp[256] = { 0, };
	int iNumCounter = 0;

	_fgetts(pBuffer, _countof(pBuffer), fp);
	_stscanf_s(pBuffer, _T("%s%d"), pTemp, _countof(pTemp), &iNumCounter);

	int iIndex = 0;
	TCHAR szInState[256] = { 0, };
	TCHAR szEventState[256] = { 0, };
	TCHAR szOutState[256] = { 0, };

	for (int iState = 0; iState < iNumCounter; ++iState)
	{
		_fgetts(pBuffer, _countof(pBuffer), fp);
		_stscanf_s(pBuffer, _T("%d%s%s%s"), &iIndex, szInState, _countof(szInState),
			szEventState, _countof(szEventState),
			szOutState, _countof(szOutState));

		AddStateTransition(GetIndex(szInState), GetIndex(szEventState), GetIndex(szOutState));
	}

	fclose(fp);
	return true;
}
ZFiniteStateMachine::ZFiniteStateMachine()
{
	//				현상태 -> 이벤트 -> 출력상태
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
