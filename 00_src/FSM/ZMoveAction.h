#pragma once
#include "Enemy.h"

class ZMoveAction : public ZEnemyState
{
public:
	bool Process(Object * pTarget) override;
public:
	ZMoveAction(ZEnemy * pOwner);
	virtual ~ZMoveAction();
};

