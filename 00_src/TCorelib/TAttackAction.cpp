#include "TAttackAction.h"


bool TAttackAction::Process(TObject* pTarget)
{
	RECT rt;
	rt.left = m_pOwner->m_pos.x - m_pOwner->m_fAttackRadius;
	rt.top = m_pOwner->m_pos.y - m_pOwner->m_fAttackRadius;
	rt.right = m_pOwner->m_pos.x + m_pOwner->m_fAttackRadius;
	rt.bottom = m_pOwner->m_pos.y + m_pOwner->m_fAttackRadius;

	m_pOwner->m_rtCollision.left = rt.left;
	m_pOwner->m_rtCollision.top = rt.top;
	m_pOwner->m_rtCollision.right = rt.right;
	m_pOwner->m_rtCollision.bottom = rt.bottom;
	
	

	tPoint vDir;
	vDir.x= pTarget->m_pos.x -m_pOwner->m_pos.x;
	vDir.y = pTarget->m_pos.y -m_pOwner->m_pos.y;

	float fLength = sqrt(vDir.x*vDir.x + vDir.y*vDir.y);
	vDir.x /= fLength;
	vDir.y /= fLength;

	fLength = sqrt(vDir.x*vDir.x + vDir.y*vDir.y);

	tPoint vPos;
	vPos.x= m_pOwner->m_pos.x +
		vDir.x * g_fSecPerFrame* m_pOwner->m_fSpeed;
	vPos.y = m_pOwner->m_pos.y +
		vDir.y * g_fSecPerFrame * m_pOwner->m_fSpeed;
	m_pOwner->Move(vPos);

	if (TCollision::RectInRect(rt, pTarget->m_rtCollision)==false)
	{
		m_pOwner->SetTransition(EVENT_LOSTTARGET);
	}
	return true;
}

TAttackAction::TAttackAction(TEnemy* pParent) :
	TEnemyState(pParent)
{
}


TAttackAction::~TAttackAction()
{
}
