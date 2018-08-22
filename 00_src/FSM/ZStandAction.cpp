#include "ZStandAction.h"

bool ZStandAction::Process(Object * pTarget)
{
	RECT rt;
	rt.left = m_pOwner->m_CenterPos.x - m_pOwner->m_fAttackRadius;
	rt.top = m_pOwner->m_CenterPos.y - m_pOwner->m_fAttackRadius;
	rt.right = m_pOwner->m_CenterPos.x + m_pOwner->m_fAttackRadius;
	rt.bottom = m_pOwner->m_CenterPos.y + m_pOwner->m_fAttackRadius;
	if (Collision::RectInPt(rt, pTarget->m_CenterPos))
	{
		m_pOwner->SetTransition(EVENT_FINDTARGET);
	}
	return true;
}

ZStandAction::ZStandAction(ZEnemy * pOwner) : ZEnemyState(pOwner)
{
}


ZStandAction::~ZStandAction()
{
}
