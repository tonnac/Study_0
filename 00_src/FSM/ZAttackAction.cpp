#include "ZAttackAction.h"
#include "Object.h"

bool ZAttackAction::Process(Object * pTarget)
{
	FloatPoint vDirection;  //Å¸°Ù°úÀÇ ¹æÇâ
	vDirection.x = pTarget->getCenterPos()->x;
	vDirection.y = pTarget->getCenterPos()->y;

	FLOAT fLength = sqrt((vDirection.x * vDirection.x) + (vDirection.y) * vDirection.y);
	vDirection.x /= fLength;
	vDirection.y /= fLength;

	fLength = sqrt((vDirection.x * vDirection.x) + (vDirection.y) * vDirection.y); //´ÜÀ§º¤ÅÍ

	FloatPoint vPos;
	vPos.x = (m_pOwner->m_pos.x * vDirection.x * g_fPerSecFrame * m_pOwner->getSpeed());

	vPos.y = (m_pOwner->m_pos.y * vDirection.y * g_fPerSecFrame * m_pOwner->getSpeed());


	return true;
}

ZAttackAction::ZAttackAction(ZEnemy * pOwner) : ZEnemyState(pOwner)
{
}


ZAttackAction::~ZAttackAction()
{
}
