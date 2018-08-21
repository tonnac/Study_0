#include "ZAttackAction.h"

bool ZAttackAction::Process(KObject * pTarget)
{
	return true;
}

ZAttackAction::ZAttackAction(ZEnemy * pOwner) : ZEnemyState(pOwner)
{
}


ZAttackAction::~ZAttackAction()
{
}
