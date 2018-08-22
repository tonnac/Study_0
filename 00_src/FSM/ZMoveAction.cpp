#include "ZMoveAction.h"

bool ZMoveAction::Process(Object * pTarget)
{
	return true;
}


ZMoveAction::ZMoveAction(ZEnemy * pOwner) : ZEnemyState(pOwner)
{
}


ZMoveAction::~ZMoveAction()
{
}
