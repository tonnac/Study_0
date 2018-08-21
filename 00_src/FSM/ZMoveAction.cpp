#include "ZMoveAction.h"

bool ZMoveAction::Process(KObject * pTarget)
{
	return true;
}


ZMoveAction::ZMoveAction(ZEnemy * pOwner) : ZEnemyState(pOwner)
{
}


ZMoveAction::~ZMoveAction()
{
}
