#include "TEnemy.h"
#include "TStandAction.h"
#include "TMoveAction.h"
#include "TAttackAction.h"
void TEnemy::Move(tPoint pos)
{
	m_pos = pos;
	int iHalfX = m_rtDraw.right / 2;
	int iHalfY = m_rtDraw.bottom / 2;
	m_posDraw.x = m_pos.x - iHalfX;
	m_posDraw.y = m_pos.y - iHalfY;
}
bool TEnemy::Move()
{
	int iHalfX = m_rtDraw.right / 2;
	int iHalfY = m_rtDraw.bottom / 2;
	if ((m_pos.x + iHalfX) > g_rtClient.right)
	{
		m_fDir[0] *= -1.0f;
		m_pos.x = g_rtClient.right - iHalfX;
	}
	if (m_pos.y + iHalfY > g_rtClient.bottom)
	{
		m_fDir[1] *= -1.0f;
		m_pos.y = g_rtClient.bottom - iHalfY;
	}
	if ((m_pos.x - iHalfX) < g_rtClient.left)
	{
		m_fDir[0] *= -1.0f;
		m_pos.x = g_rtClient.left + iHalfX;
	}
	if (m_pos.y - iHalfY < g_rtClient.top)
	{
		m_fDir[1] *= -1.0f;
		m_pos.y = g_rtClient.top + iHalfY;
	}
	m_pos.x += m_fDir[0] * m_fSpeed * g_fSecPerFrame;
	m_pos.y += m_fDir[1] * m_fSpeed * g_fSecPerFrame;
	m_posDraw.x = m_pos.x - iHalfX;
	m_posDraw.y = m_pos.y - iHalfY;
	return true;
}

TEnemy::TEnemy()
{
	m_pActionList[STATE_STAND] = new TStandAction(this);
	m_pActionList[STATE_MOVE] = new TMoveAction(this);
	m_pActionList[STATE_ATTACK] = new TAttackAction(this);	
	m_pAction = m_pActionList[STATE_STAND];
	m_dwCurrentState = STATE_STAND;
}
bool TEnemy::Process(TObject* pTarget)
{
	m_pAction->Process(pTarget);
	return true;
}
DWORD   TEnemy::SetTransition(DWORD dwEvent)
{
	m_dwCurrentState = m_pFsm->StateTransition(m_dwCurrentState, dwEvent);
	m_pAction = m_pActionList[m_dwCurrentState];
	return m_dwCurrentState;
}
TEnemy::~TEnemy()
{
	delete m_pActionList[STATE_STAND];
	delete m_pActionList[STATE_MOVE];
	delete m_pActionList[STATE_ATTACK];
}
